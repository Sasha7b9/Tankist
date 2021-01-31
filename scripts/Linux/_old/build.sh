#!/usr/bin/env bash

rm ../../generated/PiEngine/libPiEngine.so
rm ../../bin/Server
rm ../../bin/TacticsVictory
rm ../../bin/Hangar

cd ../../generated/PiEngine
make -j6

cd ../Tankist/Server
make -j6
cp -f Server ../../../bin

cd ../Hangar
make -j6
cp -f Hangar ../../../bin

cd ../../TacticsVictory/TacticsVictory
make -j6
cp -f TacticsVictory ../../../bin

cd ../../../scripts/Linux

