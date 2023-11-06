@echo off
@REM setlocal enabledelayedexpansion
echo Decrypting
echo ----------
set /p key="Enter file key: "
if "%key%"=="" (
    echo Error. Key is not defined.
    exit /b 1
)
set /p dirS="File or Directory? (d/f)?"

if "%dirS%"=="" (
    echo Error. Type is not defined.
    exit /b 1
)

set file=%~1

if /i "%dirS%"=="d" (
    atk -t d -p "%file%" -k "%key%"
) else (
    atk -t f -p "%file%" -k "%key%"
)

pause