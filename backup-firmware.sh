#!/bin/bash

avrdude \
  -p m328 \
  -c usbtiny \
  -U flash:r:"please-save-me.hex":i \
  -v
#  -b 19200 \
 
