@echo off

set _BUILD_TYPE_=debug

if "%1"=="" goto START
if %1==release set _BUILD_TYPE_=release

:START

if %_BUILD_TYPE_%==release goto START_RELEASE

:START_DEBUG
@echo on
start devenv.exe ../../generated/%_BUILD_TYPE_%/TankistU3D/TankistU3D.sln
goto EXIT

:START_RELEASE
@echo on
start devenv.exe ../../generated/%_BUILD_TYPE_%/TankistU3D/TankistU3D.sln /projectconfig Release

:EXIT
