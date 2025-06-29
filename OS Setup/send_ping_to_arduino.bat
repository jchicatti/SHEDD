
@echo off
:loop
echo PING > COM3
timeout /t 10 >nul
goto loop
