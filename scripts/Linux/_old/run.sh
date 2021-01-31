#!/usr/bin/env bash

./kill.sh

cd ../../bin
./Hangar &
./Server &
cd ../scripts/Linux
