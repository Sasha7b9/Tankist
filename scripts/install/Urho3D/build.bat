rem @echo off

if "%1" equ "" goto HINT
if "%2" neq "" goto HINT

set directory=1
set configuration=1

if %1 equ debug set directory=debug& set configuration=Debug & goto BUILD
if %1 equ release set directory=release& set configuration=Release & goto BUILD

goto HINT


:BUILD
MSBuild.exe generated/%directory%/Urho3D.sln /p:Configuration=%configuration% /t:build -clp:ErrorsOnly;WarningsOnly -nologo -m
goto EXIT

:HINT
echo.
echo Using build.bat:
echo                 build.bat [debug^|release]
echo.
goto EXIT

:EXIT
