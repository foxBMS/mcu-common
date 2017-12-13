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
 * @file    meas.h
 * @author  foxBMS Team
 * @date    02.10.2015 (date of creation)
 * @ingroup DRIVERS
 * @prefix  MEAS
 *
 * @brief   Headers for the driver for the measurements needed by the BMS (e.g., I,V,T).
 *
 */

#ifndef MEAS_IF_H_
#define MEAS_IF_H_

/*================== Includes =============================================*/
#include "meas_cfg.h"

/*================== Macros and Definitions ===============================*/

/*================== Constant and Variable Definitions ====================*/

/*================== Function Prototypes ==================================*/
extern uint8_t MEAS_IsFirstMeasurementCycleFinished(void);

/**
 * @brief   makes the requests to the LTC state machine.
 *
 * This function determines how the measurement cycle is made by the LTCs, by using the adequate state requests.
 *
 * @param   LTC_Todo       what kind of task the daisy-chain should do, taken from LTC_TASK_TYPE_e
 *
 * @return  result of the state request that was made, taken from LTC_RETURN_TYPE_e
 */
extern void MEAS_Ctrl(void);


/*================== Function Implementations =============================*/


#endif /* MEAS_IF_H_ */
