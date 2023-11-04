@echo off
set /p key="Enter the key: "
if "%key%"=="" (
    echo Key cannot be empty. Exiting.
    exit /b 1
)

rem Replace the command below with your desired command, using %key% to insert the user-provided key.
atk -t f -p "%1" -s -k "%key%"

pause