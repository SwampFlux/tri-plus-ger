#!/bin/bash

avrdude \
  -p m328 \
  -c usbtiny \
  -U flash:w:"factory-firmware.backup.hex":i \
