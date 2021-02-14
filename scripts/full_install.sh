#!/usr/bin/env bash

# *** Create links ***

dir=$PWD

cd install
./tune_ports.sh
./create_linsk.sh
cd $dir

# *** Clone and build Urho3D ***
cd install/Urho3D
./assembly.sh full all
cd $dir

# *** Build third party ***

# cd install\ThirdParty
# call make_build_all.bat
# cd %start_dir%

# rem *** Build Tankist ***
# cd Windows
# call make.bat build all
# cd %start_dir%

# call copy_dll.bat


