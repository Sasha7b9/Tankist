@echo off

if "%1" EQU "" goto HINT

if "%1" EQU "master" goto RUN_MASTER

    goto HINT

:RUN_MASTER

if %2==debug   goto RUN_MASTER
if %2==release goto RUN_MASTER

goto HINT

:RUN_MASTER
    cd ../../Tankist/out/%2%
    start Master.exe
    cd ../../../scripts/Windows
    goto EXIT

:HINT
    echo.
    echo Using run.bat:
    echo                run [master] [debug^|release^]
    echo.

:EXIT
