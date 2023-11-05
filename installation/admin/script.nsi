; Script to run as administrator, execute PowerShell, and extract files

unicode True

Outfile "ATK-Installer.exe"
RequestExecutionLevel admin

Section

; Set the installation directory to Program Files
SetOutPath $PROGRAMFILES\ATK

; Create the installation directory if it doesn't exist
CreateDirectory $PROGRAMFILES\ATK

; Copy your PowerShell script to the installation directory
File "Setup.ps1"

; Execute the PowerShell script with elevated privileges and pass the parameters
nsExec::ExecToLog 'Powershell.exe -ExecutionPolicy Bypass -File "$PROGRAMFILES\ATK\Setup.ps1" "$PROGRAMFILES\ATK" "no"'


; Extract uninstallation script
File "Uninstall.ps1"

; Extract an EXE and BAT file
File "ATK.exe"
File "atk-exe.ico"
File "encrypt_with_atk.cmd"
File "open_with_atk.cmd"
File "atk-ext.ico"
File "changelog.txt"

; Create an uninstaller in the same directory as the installer
WriteUninstaller "$PROGRAMFILES\ATK\Uninstall.exe"


; MessageBox MB_YESNO|MB_ICONQUESTION "Reboot may be required for the changes to take place. Do you wish to reboot the system?" IDNO +2
; Reboot

SectionEnd

Section "Uninstall"

; Execute the PowerShell script with elevated privileges and pass the parameters
nsExec::ExecToLog 'Powershell.exe -ExecutionPolicy Bypass -File "$PROGRAMFILES\ATK\Uninstall.ps1" "$PROGRAMFILES\ATK"'

; Remove installed files during uninstallation
Delete "$PROGRAMFILES\ATK\ATK.exe"
Delete "$PROGRAMFILES\ATK\changelog.txt"
Delete "$PROGRAMFILES\ATK\open_with_atk.cmd"
Delete "$PROGRAMFILES\ATK\atk-ext.ico"
Delete "$PROGRAMFILES\ATK\atk-exe.ico"
Delete "$PROGRAMFILES\ATK\Setup.ps1"
Delete "$PROGRAMFILES\ATK\Uninstall.ps1"
Delete "$PROGRAMFILES\ATK\"
Delete "$PROGRAMFILES\ATK\open_with_atk"
Delete "$PROGRAMFILES\ATK\open_with_atk.lnk"
Delete "$PROGRAMFILES\ATK\encrypt_with_atk"
Delete "$PROGRAMFILES\ATK\encrypt_with_atk.lnk"
Delete "$PROGRAMFILES\ATK\encrypt_with_atk.cmd"
Delete "$PROGRAMFILES\ATK\Uninstall.exe"

Delete "$SMPROGRAMS\open_with_atk.lnk"

; Remove the installation directory
RMDir $PROGRAMFILES\ATK

SectionEnd
