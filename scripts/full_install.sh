#!/usr/bin/env bash

dir=$PWD

cd install
./tune_ports.sh

# *** Create links ***
./create_links.sh
cd $dir

# *** Clone and build Urho3D ***
cd install/Urho3D
./assembly.sh full all
cd $dir

# *** Build third party ***
cd install/ThirdParty
./assembly.sh full all
./build_opus.sh
cd $dir

# rem *** Build Tankist ***
# cd Windows
# call make.bat build all
# cd %start_dir%

# call copy_dll.bat


