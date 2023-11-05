@echo off
setlocal enabledelayedexpansion
echo Encrypting
echo ----------
set /p key="Enter file key: "
if "%key%"=="" (
    echo Error. Key is not defined.
    exit /b 1
)

set /p addS="Do you want to make this file decryptable only on this computer and on current user? (y/n)? "

set file=%~1

if /i "%addS%"=="y" (
    atk -t f -p "%file%" -k "%key%" -s
) else (
    atk -t f -p "%file%" -k "%key%"
)

pause