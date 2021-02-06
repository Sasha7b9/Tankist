set current_dir=%CD%
cd ../../../..
if not exist Urho3D git clone https://github.com/urho3d/Urho3D.git
cd Urho3D
:MAKE_URHO3D
rmdir generated\debug /S /Q
cmake . -Bgenerated/debug -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_GENERATOR="Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Debug -DURHO3D_64BIT=1 -DURHO3D_THREADING=1 -DURHO3D_C++11=1 -DURHO3D_LIB_TYPE=SHARED -DURHO3D_STATIC_RUNTIME=0
MSBuild.exe generated/debug/Urho3D.sln /p:Configuration=debug /t:build -clp:ErrorsOnly;WarningsOnly -nologo /m
cd %current_dir%
