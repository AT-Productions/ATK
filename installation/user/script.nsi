; Script to run as user privilages. Run .ps1 scripts and extract files

unicode True

Outfile "ATK-Installer.exe"

Section

; Set the installation directory to Program Files
SetOutPath $APPDATA\ATK

CreateDirectory $APPDATA\ATK

; Copy your PowerShell script to the installation directory
File "Setup.ps1"

; Execute the PowerShell script with elevated privileges and pass the parameters
nsExec::ExecToLog 'Powershell.exe -ExecutionPolicy Bypass -File "$APPDATA\ATK\Setup.ps1" "$APPDATA\ATK" "no"'


; Extract uninstallation script
File "Uninstall.ps1"

; Extract an EXE and BAT file
File "ATK.exe"
File "open_with_atk.bat"
File "atk-ext.ico"

; Create an uninstaller in the same directory as the installer
WriteUninstaller "$APPDATA\ATK\Uninstall.exe"
SectionEnd


; Uninstall
Section "Uninstall"

; Execute the PowerShell script with elevated privileges and pass the parameters
nsExec::ExecToLog 'Powershell.exe -ExecutionPolicy Bypass -File "$APPDATA\ATK\Uninstall.ps1" "$APPDATA\ATK"'

; Remove installed files during uninstallation
Delete "$APPDATA\ATK\ATK.exe"
Delete "$APPDATA\ATK\open_with_atk.bat"
Delete "$PROGRAMFILES\ATK\atk-ext.ico"
Delete "$APPDATA\ATK\Setup.ps1"
Delete "$APPDATA\ATK\Uninstall.ps1"
DELETE "$APPDATA\ATK\"
DELETE "$APPDATA\ATK\Uninstall.exe"

; Remove the installation directory
RMDir $APPDATA\ATK

SectionEnd