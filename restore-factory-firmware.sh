#!/bin/bash

avrdude \
  -p m328 \
  -c usbtiny \
  -U flash:w:"factory-firmware.backup.hex":i \
  -v -v

#  -b 19200 \
#  -c arduino \
#  -P /dev/ttyUSB0 \
 
