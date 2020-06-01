#!/bin/bash

avrdude \
  -p m328 \
  -c usbtiny \
  -U flash:r:"new.tri-ger.backup.hex":i \
  -v -v
#  -P /dev/ttyUSB0 \
#  -b 19200 \
 
