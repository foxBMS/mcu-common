# foxBMS-common-drivers Change Log

## Release 1.1.0
- updated license header
- seperated database entries to prevent concurrent read/write requests to the database
- updated wscripts to build specific files only for primary/secondary
- moved sdram from common repository to primary repository
- renamed database functions to `DB_WriteBlock()` and `DB_ReadBlock()`
- There was a compile error when CAN0 and CAN1 are deactivated
- updated README.md

## Release 1.0.2

- There was an error in the LTC module when less than 12 battery cells per module were used. An overflow occurred 
in function LTC_SaveRXtoVoltagebuffer() and invalid cell voltages were saved in the database.
-mcu-common/src/module/ltc.c: fixed function LTC_SetMUXChCommand()
-mcu-common/src/module/ltc.c: redesigned structure for automatic measurement and 50Hz voltage measurement
-mcu-common/src/module/ltc.c: LTC driver now uses interrupts
-mcu-common/src/module/ltc.c: implemented/improved access to slave features (IO port-expander, external temperature sensor, EEPROM)


## Release 1.0.0

Initial release of this repository containing drivers that are shared across
the mcus.

## 0.0.3 2017-10-23 Common engine moved to this repository
- The driver of the database is moved to the common-repository. The wscripts
  in the proejct repositories need to be updated.
- Added/changed/deleted files:
  - src/engine/wscript: added includes and c files to be built
  - src/engine/{database}: common engine moved

## 0.0.2 2017-09-21 Common drivers moved to this repository
- The drivers that are shared entirely between the primary and secondary MCU 
have been removed from the MCU specific repositories and added to this 
repository.
- Added/changed/deleted files:
  - src/module/wscript: added includes and c files to be built
  - src/module/{chksum, dma, ltc, mcu, rcc, watchdog}: common drivers moved
 
## 0.0.1 2017-09-20 Initial Commit
- Creation of the repository to store common driver between the foxBMS-primary
mcu and the foxBMS secondary mcu. To be able to use this, we have to change 
some drivers, as there are some configuration dependent lines in the drivers.
After we fixed this, we can place the common drivers in this repository.
- Added/changed/deleted files:
  - src/wscript: standard wscript for src directory of a foxBMS c-source 
    directory
  - src/module/wscript: placeholder wscript for the low level directory of a 
   foxBMS c-source directory
  - .clang-format: standard foxBMS clang-format file
  - .gitignore: standard foxBMS .gitignore file for c-source repositories
  - CHANGELOG.md: Initial commit of the change log
  - LICENSE.md: added the foxBMS software license
  - README.md: added a README placeholder
  - wscript: standard wscript for the top directory of a foxBMS c-source 
    directory
