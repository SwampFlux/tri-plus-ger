#!/bin/bash

avrdude \
  -p m328p \
  -c avrisp \
  -P /dev/ttyUSB0 \
  -b 19200 \
  -U flash:r:"new.tri-ger.backup.hex":i \
  -F
  -v -v

