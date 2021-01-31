@echo off

if "%~1"=="" goto HINT
if "%~2" NEQ "" goto HINT

@echo .
@echo %TIME%   Making Full PiEngine2 %1 ...

cd ../..

set BUILDING=debug
set CMAKE_BUILD=Debug

if %1==release set BUILDING=release
if %1==release set CMAKE_BUILD=Release

rem Путь к каталогу с решением PiEngine2.sln
set CMAKE_PROJECT_DIR="generated/%BUILDING%/Engine"

rem Путь к каталогу с релизной версией PiEngine
set ENGINE_OUT_DIR=%PROJECT_TANKIST_DIR%\out\%BUILDING%

rem Путь к каталогу Tactics Victory
set VICTORY_OUT_DIR=%PROJECT_TANKIST_DIR%\TacticsVictory\out\%BUILDING%

rem Путь к каталогу Tankist
set TANKIST_OUT_DIR=%PROJECT_TANKIST_DIR%\Tankist\out\%BUILDING%

rem Пути к каталогам с плагинами
set PLUGINS_OUT_DIR=%PROJECT_TANKIST_DIR%\out\%BUILDING%\Plugins
set PLUGINS_TOOLS_OUT_DIR=%PROJECT_TANKIST_DIR%\out\%BUILDING%\Plugins\Tools
set PLUGINS_TOOLS_EDITOR_OUT_DIR=%PROJECT_TANKIST_DIR%\out\%BUILDING%\Plugins\Tools\Editor
set PLUGINS_TOOLS_FONTS_OUT_DIR=%PROJECT_TANKIST_DIR%\out\%BUILDING%\Plugins\Tools\Fonts

rmdir %CMAKE_PROJECT_DIR% /S /Q

mkdir %CMAKE_PROJECT_DIR%

@echo on

cmake Source/Source/CMakeLists.txt -B%CMAKE_PROJECT_DIR% -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_GENERATOR="Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=%CMAKE_BUILD%

@echo off

cd scripts/Windows

@echo %TIME%   Complete

goto EXIT

:HINT

echo.
echo Using make.bat:  make [debug^|release]
echo.
    
    
:EXIT