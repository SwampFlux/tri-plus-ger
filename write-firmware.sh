#!/bin/bash
parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )

# build code
#arduino \
#  --verify
#  --board arduino:avr:nano:cpu=atmega328
#  --preserve-temp-files
#  --verbose-build
#  --pref build.path "$parent_path/build/"

# make sure the build was successful...
#if [ $? -eq 0 ]; then
#  echo OK!!

  # force the hex file
  avrdude \
    -p m328 \
    -c usbtiny \
    -U flash:w:"$1":i \
    
#else
#  echo FAIL
#fi
