#!/usr/bin/env bash

set -e

dir=$PWD

cd ../../../src/ThirdParty/opus

rm -R -f generated

cmake . -Bgenerated -G "CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release

cd generated

make -j$(nproc)

make

cd $dir
