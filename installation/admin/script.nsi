; Script to run as administrator, execute PowerShell, and extract files

unicode True
!include LogicLib.nsh

Outfile "ATK-Installer.exe"
RequestExecutionLevel admin

BrandingText /TRIMCENTER "ATK-Installer 1.4.0"
Name "ATK-Installer 1.4.0"
ManifestSupportedOS Win10
DetailsButtonText "Show progress"

######### LICENSE ############
PageEx license
    LicenseText "Readme"
    LicenseData LICENSE.txt
    LicenseForceSelection checkbox
PageExEnd

########### COMPONENTS #####################

InstType "Full" IT_FULL
InstType "Minimal" IT_MIN

PageEx components
    ComponentText "Choose files you want to install." \
    "About" \
    "Main program contains all necessary components for basic functioning. \
    Additional programs contains all extra files, mainly used by the context menu."

PageExEnd

SectionGroup "!Main Program" RO
    Section !ATK.exe sec1_id
        SectionInstType ${IT_FULL} ${IT_MIN} RO
        File "ATK.exe"
    SectionEnd
        Section LICENSE.txt sec7_id
        SectionInstType ${IT_FULL} ${IT_MIN} RO
        File "License.txt"
    SectionEnd
SectionGroupEnd

SectionGroup "Additional Components"
    Section encrypt_with_atk.cmd sec2_id
        SectionInstType ${IT_FULL}
        File "encrypt_with_atk.cmd"
    SectionEnd

    Section open_with_atk.cmd sec3_id
        SectionInstType ${IT_FULL}
        File "open_with_atk.cmd"
    SectionEnd

    Section atk-ext.ico sec4_id
        SectionInstType ${IT_FULL}
        File "atk-ext.ico"
    SectionEnd

    Section atk-exe.ico sec5_id
        SectionInstType ${IT_FULL}
        File "atk-exe.ico"
    SectionEnd

    Section changelog.txt sec6_id
        SectionInstType ${IT_FULL}
        File "changelog.txt"
    SectionEnd

SectionGroupEnd


############ DIRECTORY ######################
Var INSTALL_DIR


; Set the default installation directory
Function .onInit
    InitPluginsDir
    StrCpy $INSTALL_DIR $PROGRAMFILES64
FunctionEnd

PageEx directory
    DirVar $INSTALL_DIR
    DirVerify leave
PageExEnd


Page instfiles

########## START ##########
Section 

; Set the installation directory to Program Files
SetOutPath $INSTALL_DIR\ATK


; Create the installation directory if it doesn't exist
CreateDirectory $INSTALL_DIR\ATK



########################### SETUP ###########################
; Copy your PowerShell script to the installation directory
File "Setup.ps1"
File "RestartExplorer.ps1"

; Execute the PowerShell script with elevated privileges and pass the parameters
nsExec::ExecToLog 'Powershell.exe -ExecutionPolicy Bypass -File "$INSTALL_DIR\ATK\Setup.ps1" "$INSTALL_DIR\ATK" "no"'

; After setup, delete the file
Delete "$INSTALL_DIR\ATK\Setup.ps1"


; Asks user if they want to restart explorer and clear icon cache
MessageBox MB_YESNO|MB_ICONQUESTION "Do you want restart explorer.exe? This is needed for the icons to update." IDYES trueM IDNO falseM
trueM:
    ; Execute the PowerShell script with elevated privileges
    nsExec::ExecToLog 'Powershell.exe -ExecutionPolicy Bypass -File "$INSTALL_DIR\ATK\RestartExplorer.ps1"'
falseM:

; Delete the file
Delete "$INSTALL_DIR\ATK\RestartExplorer.ps1"

########################### EXTRACT ###########################
; Extract uninstallation script
File "Uninstall.ps1"

; Set the file attributes to hidden
System::Call 'kernel32::SetFileAttributes(t "$INSTALL_DIR\ATK\Uninstall.ps1", i 2) i .r0'

; Check if the SetFileAttributes call succeeded
${If} $0 != 0
    DetailPrint "Uninstall.ps1 file attributes set to hidden."
${Else}
    DetailPrint "Failed to set Uninstall.ps1 file attributes to hidden."
${EndIf}

; Extract files that user has chosen

## MAIN PROGRAM ##
${If} ${SectionIsSelected} ${sec1_id}
    File "ATK.exe"
${EndIf}

${If} ${SectionIsSelected} ${sec7_id}
    File "License.txt"
${EndIf}

## ADDITIONAL COMPONENTS ##

${If} ${SectionIsSelected} ${sec2_id}
    File "encrypt_with_atk.cmd"
${EndIf}

${If} ${SectionIsSelected} ${sec3_id}
    File "open_with_atk.cmd"
${EndIf}

${If} ${SectionIsSelected} ${sec4_id}
    File "atk-ext.ico"
${EndIf}

${If} ${SectionIsSelected} ${sec5_id}
    File "atk-exe.ico"
${EndIf}

${If} ${SectionIsSelected} ${sec6_id}
    File "changelog.txt"
${EndIf}


; Create an uninstaller in the same directory as the installer
WriteUninstaller "$INSTALL_DIR\ATK\Uninstall.exe"

SectionEnd



########## UNINSTALL ##########


UninstPage uninstConfirm
UninstPage instfiles


Section "Uninstall"

; Execute the PowerShell script with elevated privileges and pass the parameters
nsExec::ExecToLog 'Powershell.exe -ExecutionPolicy Bypass -File "$INSTALL_DIR\ATK\Uninstall.ps1" "$INSTALL_DIR\ATK"'

########################### DELETE FILES ###########################
; Remove installed files during uninstallation

Delete "$INSTALL_DIR\ATK\ATK.exe"
Delete "$INSTALL_DIR\ATK\Uninstall.exe"

Delete "$INSTALL_DIR\ATK\changelog.txt"
Delete "$INSTALL_DIR\ATK\LICENSE.txt"

Delete "$INSTALL_DIR\ATK\atk-ext.ico"
Delete "$INSTALL_DIR\ATK\atk-exe.ico"

Delete "$INSTALL_DIR\ATK\Setup.ps1"
Delete "$INSTALL_DIR\ATK\Uninstall.ps1"

Delete "$INSTALL_DIR\ATK\open_with_atk.cmd"
Delete "$INSTALL_DIR\ATK\encrypt_with_atk.cmd"
Delete "$INSTALL_DIR\ATK\open_with_atk.lnk"
Delete "$INSTALL_DIR\ATK\encrypt_with_atk.lnk"

Delete "$SMPROGRAMS\open_with_atk.lnk"

; Remove the installation directory
RMDir $INSTALL_DIR\ATK

SectionEnd