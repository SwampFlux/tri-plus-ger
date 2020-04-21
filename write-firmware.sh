#!/bin/bash

avrdude \
  -p m328p \
  -c usbtiny \
  -U flash:w:"tri_ger_plus.cpp.hex":i \
  -F
  -v -v
#  -P /dev/ttyUSB0 \
#  -b 19200 \
 
