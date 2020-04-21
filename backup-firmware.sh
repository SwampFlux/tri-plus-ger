#!/bin/bash

avrdude \
  -p m328p \
  -c usbtiny \
  -U flash:r:"new.tri-ger.backup.hex":i \
  -F
  -v -v
#  -P /dev/ttyUSB0 \
#  -b 19200 \
 
