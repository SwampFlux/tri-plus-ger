#!/bin/bash

#cp $arg1 ./

echo "writing file" $1

avrdude \
  -p m328p \
  -c usbtiny \
  -U flash:w:$1:i \
  -F
#  -P /dev/ttyUSB0 \
#  -b 19200 \
 
