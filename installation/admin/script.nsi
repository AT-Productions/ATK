; Script to run as administrator, execute PowerShell, and extract files

unicode True
!include LogicLib.nsh

Outfile "ATK-Installer.exe"
RequestExecutionLevel admin

BrandingText /TRIMCENTER "ATK 1.4.0 Setup"
Name "ATK 1.4.0 Setup"
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
    Additional components contain all extra files, mainly used by the context menu."
PageExEnd

SectionGroup "!Main Program" RO
    Section !ATK.exe sec1_id
        SectionInstType ${IT_FULL} ${IT_MIN} RO
    SectionEnd
    Section !LICENSE.txt sec7_id
        SectionInstType ${IT_FULL} ${IT_MIN} RO
    SectionEnd
    Section !Uninstall.ps1 sec8_id
        SectionInstType ${IT_FULL} ${IT_MIN} RO
    SectionEnd
    Section !RestartExplorer.ps1 sec9_id
        SectionInstType ${IT_FULL} ${IT_MIN} RO
    SectionEnd
SectionGroupEnd

SectionGroup "Additional Components"
    Section encrypt_with_atk.cmd sec2_id
        SectionInstType ${IT_FULL}
    SectionEnd

    Section open_with_atk.cmd sec3_id
        SectionInstType ${IT_FULL}
    SectionEnd

    Section atk-ext.ico sec4_id
        SectionInstType ${IT_FULL}
    SectionEnd

    Section atk-exe.ico sec5_id
        SectionInstType ${IT_FULL}
    SectionEnd

    Section changelog.txt sec6_id
        SectionInstType ${IT_FULL}
    SectionEnd
SectionGroupEnd

############ DIRECTORY ######################
Var INSTALL_DIR

; Set the default installation directory
Function .onInit
    InitPluginsDir
    StrCpy $INSTALL_DIR $PROGRAMFILES64\ATK
FunctionEnd

PageEx directory
    DirVar $INSTALL_DIR
    DirVerify leave
PageExEnd

Function .onVerifyInstDir
    Var /GLOBAL ext
    StrCpy $ext "ATK"
    StrCpy $INSTALL_DIR "$INSTALL_DIR$ext"
FunctionEnd

PageEx instfiles
PageExEnd
############################## START ##############################
Section 
; Set the installation directory
SetOutPath $INSTALL_DIR

; Create the installation directory if it doesn't exist
CreateDirectory $INSTALL_DIR
SectionEnd

########## INSTALLATION AND EXTRACTION ##########
Section 

; Extract uninstallation script
File "Uninstall.ps1"

; Set the file attributes to hidden
System::Call 'kernel32::SetFileAttributes(t "$INSTALL_DIR\Uninstall.ps1", i 2) i .r0'

; Check if the SetFileAttributes call succeeded
${If} $0 != 0
    DetailPrint "Uninstall.ps1 file attributes set to hidden."
${Else}
    DetailPrint "Failed to set Uninstall.ps1 file attributes to hidden."
${EndIf}

; Extract files based on section selection

########## MAIN PROGRAM ##########
${If} ${SectionIsSelected} ${sec1_id}
    File "ATK.exe"
${EndIf}

${If} ${SectionIsSelected} ${sec7_id}
    File "License.txt"
${EndIf}

########## ADDITIONAL COMPONENTS ##########

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
WriteUninstaller "$INSTALL_DIR\Uninstall.exe"

SectionEnd



########## UNINSTALL ##########


UninstPage uninstConfirm
UninstPage instfiles


Section "Uninstall"
; Execute the PowerShell script with elevated privileges and pass the parameters
nsExec::ExecToLog 'Powershell.exe -ExecutionPolicy Bypass -File "$INSTDIR\Uninstall.ps1" "$INSTDIR"'

########################### DELETE FILES ###########################
; Remove installed files during uninstallation

Delete "$INSTDIR\ATK.exe"
Delete "$INSTDIR\Uninstall.exe"

Delete "$INSTDIR\changelog.txt"
Delete "$INSTDIR\LICENSE.txt"

Delete "$INSTDIR\atk-ext.ico"
Delete "$INSTDIR\atk-exe.ico"

Delete "$INSTDIR\Uninstall.ps1"

Delete "$INSTDIR\open_with_atk.cmd"
Delete "$INSTDIR\encrypt_with_atk.cmd"

; Remove the installation directory
RMDir $INSTDIR

SectionEnd