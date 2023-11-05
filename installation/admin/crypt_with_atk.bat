@echo off
echo Encrypting
echo --------
set /p key="Enter file key: "
if "%key%"=="" (
    echo Error. Key is not defined.
    exit /b 1
)

set /p addS="Do you want to make it decryptable in this PC only? (y/n)? "

set file=%~1

if /i "%addS%"=="y" (
    atk -t f -p "%file%" -k "%key%" -s
) else (
    atk -t f -p "%file%" -k "%key%"
)

pause