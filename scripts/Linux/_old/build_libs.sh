#!/usr/bin/env bash

rm -r ../../generated/ThirdParty/SLikeNet
mkdir ../../generated
mkdir ../../generated/ThirdParty
mkdir ../../generated/ThirdParty/SLikeNet
cmake ../../Source/ThirdParty/CMakeLists.txt -G "CodeBlocks - Unix Makefiles" -B../../generated/ThirdParty

cd ../../generated/ThirdParty/SLikeNet
make -j6
cd ../../../scripts/Linux
