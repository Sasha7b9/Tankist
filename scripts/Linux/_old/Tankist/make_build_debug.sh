#!/usr/bin/env bash

rm -R ../../../generated/debug/Tankist

cmake ../../../Source/ThirdParty/CMakeLists.txt -G "CodeBlocks - Unix Makefiles"  -B../../../generated/debug/ThirdParty -DCMAKE_BUILD_TYPE=Debug

cd ../../../generated/debug/ThirdParty

mkdir bin

make -j4

cp cppfs/libcppfsd.so bin
cp sockpp/libsockpp.a bin
