#!/usr/bin/env bash

rm -R -f generated

cmake . -Bgenerated -G "CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DURHO3D_64BIT=1 -DURHO3D_THREADING=1

dir=$PWD
cd generated
make -j$(nproc)
make install
cd $dir
