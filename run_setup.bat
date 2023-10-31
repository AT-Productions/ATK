@echo off
:: Check if the script is running with administrator privileges
net session >nul 2>&1
if %errorlevel% neq 0 (
    echo You need to run this script as an administrator.
    echo Please right-click on the script and select "Run as administrator."
    pause
    exit /b 1
)
echo Don't close this window while the setup is running!
echo Running powershell script: Setup.ps1
SET mypath=%~dp0
powershell.exe -ExecutionPolicy Bypass -File %mypath:~0,-1%\installation\admin\Setup.ps1 "%mypath:~0,-1%" "manual"
pause