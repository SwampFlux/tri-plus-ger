#!/bin/bash

avrdude \
  -p m328p \
  -c avrisp \
  -P /dev/ttyUSB0 \
  -b 19200 \
  -U eeprom:r:"new.tri-ger.eeprom.backup.hex":i \
  -F
  -v -v

