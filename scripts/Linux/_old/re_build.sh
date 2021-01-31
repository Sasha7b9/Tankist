#!/usr/bin/env bash

rm -r ../../generated
mkdir ../../generated
cmake CMakeLists.txt -G "CodeBlocks - Unix Makefiles" -B../../generated/
./build.py
