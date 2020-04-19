#!/bin/bash

avrdude \
  -p m328p \
  -c arduino \
  -P /dev/ttyUSB0 \
  -U eeprom:r:"new.tri-ger.eeprom.backup.hex":i \
  -v -v

#  -b 19200 \
