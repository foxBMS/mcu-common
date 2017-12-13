# foxBMS-common-drivers Change Log

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
