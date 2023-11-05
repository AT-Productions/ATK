@echo off
setlocal enabledelayedexpansion
set /p key="Enter file key: "
if "%key%"=="" (
    echo Error. Key is not defined.
    exit /b 1
)

set file=%~1

atk -t f -p "%file%" -k "%key%"

pause