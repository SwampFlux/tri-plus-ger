#!/bin/bash

avrdude \
  -p m328p \
  -c arduino \
  -P /dev/ttyUSB0 \
  -U flash:w:"tri_ger_plus.cpp.hex":i \
  -v -v

#  -b 19200 \
