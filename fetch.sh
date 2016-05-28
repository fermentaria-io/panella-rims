#!/bin/bash

one_wire=http://www.pjrc.com/teensy/arduino_libraries/OneWire.zip

curl $one_wire -o one_wire.zip
unzip one_wire.zip -d lib

