@echo off
set /p key="Enter file key: "
if "%key%"=="" (
    echo Error. Key is not defined.
    exit /b 1
)

set /p addS="Do you want to make it decryptable in this PC only? (y/n)? "
if /i "%addS%"=="y" (
    atk -t f -p "%1" -s -k "%key%"
) else (
    atk -t f -p "%1" -k "%key%"
)

pause
