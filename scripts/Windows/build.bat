@echo off

if "%1" EQU "" goto HINT

if %1==debug   goto RUN_DEBUG
if %1==release goto RUN_RELEASE
if %1==all     goto RUN_ALL

goto HINT

:RUN_DEBUG
    python build.py debug build
    goto EXIT

:RUN_RELEASE
    python build.py release build
    goto EXIT

:RUN_ALL
    python build.py debug build
    python build.py release build
    goto EXIT

:HINT
    echo.
    echo Using build.bat:  build [debug^|release^|all]
    echo.
    goto EXIT

:EXIT
