@echo off
set /p key="Enter file key: "
if "%key%"=="" (
    echo Error. Key is not defined.
    exit /b 1
)

atk -t f -p "%1" -s -k "%key%"

exit