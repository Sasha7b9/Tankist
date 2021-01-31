@echo off

if "%1" EQU "" goto HINT
if %1==debug goto PROC_DEBUG
if %1==release goto PROC_RELEASE
if %1==all goto PROC_ALL

if %1==build goto MAKE_BUILD
  
goto HINT

:PROC_DEBUG

call proc/proc_make.bat debug
goto EXIT

:PROC_RELEASE

call proc/proc_make.bat release
goto EXIT

:PROC_ALL

call proc/proc_make.bat debug
call proc/proc_make.bat release
goto EXIT

:HINT
echo.
echo Using make.bat:  make [build] [debug^|release^|all]
echo.
goto EXIT

:MAKE_BUILD

if "%2" EQU "" goto HINT
if %2==debug goto MAKE_BUILD_DEBUG
if %2==release goto MAKE_BUILD_RELEASE
if %2==all goto MAKE_BUILD_ALL

goto HINT

:MAKE_BUILD_DEBUG

call proc/proc_make.bat debug
build.bat debug
goto EXIT

:MAKE_BUILD_RELEASE

call proc/proc_make.bat release
build.bat release
goto EXIT

:MAKE_BUILD_ALL

call proc/proc_make.bat debug
call proc/proc_make.bat release
build.bat all
goto exit

:EXIT
