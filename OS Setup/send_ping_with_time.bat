
@echo off
:loop
for /f "tokens=1-2 delims=:" %%a in ('time /t') do (
    set hour=%%a
    set min=%%b
)
setlocal enabledelayedexpansion
set h=!hour!
if "!h:~0,1!"==" " set h=0!h:~1,1!
echo PING|!h!:!min! > COM3
timeout /t 5 >nul
goto loop
