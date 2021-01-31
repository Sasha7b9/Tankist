#!/usr/bin/env bash

pkill -f ./Hangar

./build.py

cd ../../bin
./Hangar
cd ../scripts/Linux

