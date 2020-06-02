#!/bin/bash

avrdude \
  -p m328 \
  -c usbtiny \
  -U eeprom:r:"new.tri-ger.eeprom.backup.hex":i \
  -v -v

#  -P /dev/ttyUSB0 \
#  -b 19200 \
 
