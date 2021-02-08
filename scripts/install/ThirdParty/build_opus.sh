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



#rmdir generated
#cmake . -Bgenerated -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_GENERATOR="Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Release
#MSBuild.exe generated/Opus.sln /p:Configuration=release /t:build -clp:ErrorsOnly -nologo /m
