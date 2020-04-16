#!/bin/bash

avrdude \
  -p m328p \
  -c arduino \
  -P /dev/ttyUSB0 \
  -U flash:r:"new.tri-ger.backup.hex":i \
  -v -v

#  -b 19200 \
