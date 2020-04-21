#!/bin/bash

avrdude \
  -p m328p \
  -c usbtiny \
  -U eeprom:r:"new.tri-ger.eeprom.backup.hex":i \
  -F
  -v -v

#  -P /dev/ttyUSB0 \
#  -b 19200 \
 
