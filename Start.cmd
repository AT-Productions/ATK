@echo off
setlocal

:: Check if the script is running with administrator privileges
net session >nul 2>&1
if %errorlevel% neq 0 (
    echo You need to run this script as an administrator.
    echo Please right-click on the script and select "Run as administrator."
    pause
    exit /b 1
)

ECHO Adding %cd% to the PATH environment variable

set PATH=%PATH%;%cd% /m & :: Adds current dir to env. vars

ECHO Setting PATHEXT environment variable

set PATHEXT=%PATHEXT%;.atk /m & :: Adds .atk to PATHEXT


:: ADD TO REG ED HKEY_CLASSES_ROOT
::  FOR .atk file


ECHO Restart your command prompt

:: ! DELETE ON RELEASE !
pause
