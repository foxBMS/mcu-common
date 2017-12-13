/**
 *
 * @copyright &copy; 2010 - 2017, Fraunhofer-Gesellschaft zur Foerderung der angewandten Forschung e.V. All rights reserved.
 *
 * BSD 3-Clause License
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 * 1.  Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * We kindly request you to use one or more of the following phrases to refer to foxBMS in your hardware, software, documentation or advertising materials:
 *
 * &Prime;This product uses parts of foxBMS&reg;&Prime;
 *
 * &Prime;This product includes parts of foxBMS&reg;&Prime;
 *
 * &Prime;This product is derived from foxBMS&reg;&Prime;
 *
 */

/**
 * @file    meas.c
 * @author  foxBMS Team
 * @date    11.11.2016 (date of creation)
 * @ingroup DRIVERS
 * @prefix  MEAS
 *
 * @brief   Driver for the measurements needed by the BMS (e.g., I,V,T).
 *
 */

/*================== Includes =============================================*/
#include "general.h"
#include "meas.h"
#include "ltc.h"


/*================== Macros and Definitions ===============================*/

/*================== Constant and Variable Definitions ====================*/
static uint32_t ltc_task_1ms_cnt = 0;
static uint8_t ltc_taskcycle = 0;



/*================== Function Prototypes ==================================*/
extern uint8_t MEAS_IsFirstMeasurementCycleFinished(void);


/*================== Function Implementations =============================*/


void MEAS_Ctrl(void)
{
    LTC_STATEMACH_e ltcstate = LTC_STATEMACH_UNDEFINED;

    LTC_TASK_TYPE_e LTC_Todo = LTC_HAS_TO_MEASURE;

    ltc_task_1ms_cnt++;

    if(LTC_GetStateRequest() == LTC_STATE_NO_REQUEST)
    {
        ltcstate = LTC_GetState();

        if(LTC_Todo == LTC_HAS_TO_MEASURE)
        {
            if(ltcstate == LTC_STATEMACH_UNINITIALIZED)
            {
                /* set initialization request*/
                LTC_SetStateRequest(LTC_STATE_INIT_REQUEST, LTC_ADCMODE_UNDEFINED, LTC_ADCMEAS_UNDEFINED, LTC_NUMBER_OF_MUX_MEASUREMENTS_PER_CYCLE);
                ltc_taskcycle=1;
            }
            else if(ltcstate == LTC_STATEMACH_IDLE)
            {
                /* set state requests for starting measurement cycles if LTC is in IDLE state*/
                ++ltc_taskcycle;

                switch(ltc_taskcycle)
                {
                case 2:
                    LTC_SetStateRequest(LTC_STATE_VOLTAGEMEASUREMENT_REQUEST,LTC_VOLTAGE_MEASUREMENT_MODE,LTC_ADCMEAS_ALLCHANNEL, LTC_NUMBER_OF_MUX_MEASUREMENTS_PER_CYCLE);
                    break;

                case 3:
                    LTC_SetStateRequest(LTC_STATE_READVOLTAGE_REQUEST,LTC_VOLTAGE_MEASUREMENT_MODE,LTC_ADCMEAS_ALLCHANNEL, LTC_NUMBER_OF_MUX_MEASUREMENTS_PER_CYCLE);
                    break;

                case 4:
                    LTC_SaveVoltages();
                    LTC_SetStateRequest(LTC_STATE_BALANCECONTROL_REQUEST,LTC_VOLTAGE_MEASUREMENT_MODE,LTC_ADCMEAS_ALLCHANNEL, LTC_NUMBER_OF_MUX_MEASUREMENTS_PER_CYCLE);
                    break;

                case 5:
                    LTC_SetStateRequest(LTC_STATE_MUXMEASUREMENT_REQUEST,LTC_GPIO_MEASUREMENT_MODE,LTC_ADCMEAS_SINGLECHANNEL_GPIO1, LTC_NUMBER_OF_MUX_MEASUREMENTS_PER_CYCLE);
                    break;

                case 6:
                    if (LTC_GetMuxSequenceState() == E_OK) {
                        LTC_SaveTemperatures();
                    }
                    LTC_SetStateRequest(LTC_STATE_USER_IO_REQUEST,LTC_ADCMODE_NORMAL_DCP0,LTC_ADCMEAS_ALLCHANNEL, LTC_NUMBER_OF_MUX_MEASUREMENTS_PER_CYCLE);
                    break;

                case 7:
                    LTC_SetStateRequest(LTC_STATE_EEPROM_READ_UID_REQUEST,LTC_ADCMODE_NORMAL_DCP0,LTC_ADCMEAS_ALLCHANNEL, LTC_NUMBER_OF_MUX_MEASUREMENTS_PER_CYCLE);
                    break;

                case 8:
                    LTC_SetStateRequest(LTC_STATE_TEMP_SENS_READ_REQUEST,LTC_ADCMODE_NORMAL_DCP0,LTC_ADCMEAS_ALLCHANNEL, LTC_NUMBER_OF_MUX_MEASUREMENTS_PER_CYCLE);
                    break;

                case 9:
                    LTC_SetStateRequest(LTC_STATE_ALLGPIOMEASUREMENT_REQUEST,LTC_ADCMODE_NORMAL_DCP0,LTC_ADCMEAS_ALLCHANNEL, LTC_NUMBER_OF_MUX_MEASUREMENTS_PER_CYCLE);
                    break;

                case 10:
                    LTC_SaveAllGPIOs();
                    ltc_taskcycle = 1;            // Restart measurement cycle
                    LTC_SetFirstMeasurementCycleFinished(); //set first measurement finished flag
                    break;

                default:
                    ltc_taskcycle = 1;
                    break;
                }
            }
        }

        else if(LTC_Todo == LTC_HAS_TO_REINIT)
        {
            if(ltcstate != LTC_STATEMACH_INITIALIZATION || ltcstate != LTC_STATEMACH_INITIALIZED)
            {
                ltc_taskcycle=1;
                LTC_SetStateRequest(LTC_STATE_REINIT_REQUEST,LTC_ADCMODE_UNDEFINED, LTC_ADCMEAS_UNDEFINED, LTC_NUMBER_OF_MUX_MEASUREMENTS_PER_CYCLE);
            }
        }

        else if(LTC_Todo == LTC_HAS_TO_MEASURE_2CELLS)
        {
            if(ltcstate == LTC_STATEMACH_UNINITIALIZED)
                {
                    /* set initialization request */
                    LTC_SetStateRequest(LTC_STATE_INIT_REQUEST, LTC_ADCMODE_FAST_DCP0, LTC_ADCMEAS_SINGLECHANNEL_TWOCELLS, LTC_NUMBER_OF_MUX_MEASUREMENTS_PER_CYCLE);
                    ltc_taskcycle=1;
                }
            else if(ltcstate == LTC_STATEMACH_IDLE)
            {
                /* set state requests for starting measurement cycles if LTC is in IDLE state */

                ++ltc_taskcycle;

                switch(ltc_taskcycle)
                {

                case 2:
                    LTC_SetStateRequest(LTC_STATE_VOLTAGEMEASUREMENT_2CELLS_REQUEST,LTC_ADCMODE_FAST_DCP0,LTC_ADCMEAS_SINGLECHANNEL_TWOCELLS, LTC_NUMBER_OF_MUX_MEASUREMENTS_PER_CYCLE);
                    break;

                case 3:
                    LTC_SetStateRequest(LTC_STATE_READVOLTAGE_2CELLS_REQUEST,LTC_ADCMODE_FAST_DCP0,LTC_ADCMEAS_SINGLECHANNEL_TWOCELLS, LTC_NUMBER_OF_MUX_MEASUREMENTS_PER_CYCLE);
                    break;


                case 4:
                    LTC_SaveVoltages();
                    // retVal = LTC_SetStateRequest(LTC_STATE_MUXMEASUREMENT_REQUEST,LTC_GPIO_MEASUREMENT_MODE,LTC_ADCMEAS_SINGLECHANNEL, LTC_NUMBER_OF_MUX_MEASUREMENTS_PER_CYCLE);
                    ltc_taskcycle=1;            // Restart measurement cycle
                    break;

                default:
                    ltc_taskcycle=1;
                    break;
                }
            }
        }
    }
}



extern uint8_t MEAS_IsFirstMeasurementCycleFinished(void){

    uint8_t retval = FALSE;

    retval    = LTC_IsFirstMeasurementCycleFinished();

    return (retval);
}
