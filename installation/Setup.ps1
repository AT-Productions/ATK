

# Check if the script is running with administrator privileges
$isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")
if (-not $isAdmin) {
    Write-Host "You need to run this script as an administrator."
    Write-Host "Please right-click on the script and select 'Run as administrator.'"
    pause
    exit 1
}
# Argument got from run_setup.bat
# Contains the directory it was called from
# Maybe use $PSScriptRoot in future?
$callDir = $args[0]


# Windows PATH Environment Variable Setup
#
# ---------------------------------------------------------------------
# Add the current directory to the PATH environment variable
# Check if folder $callDir is already in the path
if($Env:PATH -notlike "*$callDir*"){
    # TRUE, ADD TO PATH

    Write-Host Adding current path to System Environmental Variables.

    # Make oldPath and newPath variables
    $oldpath = (Get-ItemProperty -Path 'Registry::HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\Environment' -Name PATH).path
    $newpath = "$oldpath;$callDir"
    
    Set-ItemProperty -Path 'Registry::HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\Environment' -Name PATH -Value $newpath

    Write-Host Added current path to System Environmental Variables.
} else {
	# FALSE DON'T ADD
    Write-Host Current path is already found in System Environmental Variables.
}

# ---------------------------------------------------------------------

# Windows PATHEXT Environmental Variable Setup
#
# ---------------------------------------------------------------------
# Setting the PATHEXT environment variable
$oldpathext = (Get-ItemProperty -Path 'Registry::HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\Environment' -Name PATHEXT).pathext

$newpathext = "$oldpathext;.atk"

# Check if .atk is already in the pathext
if($Env:PATHEXT -notlike "*.atk*"){
    # TRUE, ADD TO PATHEXT
    Write-Host Adding .atk to PATHEXT.
    Set-ItemProperty -Path 'Registry::HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\Environment' -Name PATHEXT -Value $newpathext
    Write-Host Added .atk to PATHEXT.
} else {
    # FALSE, DON'T ADD
    Write-Host .atk already found in PATHEXT.
}
# ---------------------------------------------------------------------



# Windows HKCR Setup
#
# ---------------------------------------------------------------------
# Define the registry keys and values to create
$registryKeyPath = "HKCR\.atk"
$registryKeyValuePerceivedType = "PerceivedType"
$registryKeyValuePerceivedTypeValue = "text"
$registryShellKeyPath = "HKCR\.atk\shell\Open with ATK"
$registryCommandKeyPath = "HKCR\.atk\shell\Open with ATK\command"
$registryCommandKeyValue = "open_with_atk.cmd `"%%1`""  # Note the double percent signs

# Create registry entries
reg.exe add "$registryKeyPath" /v "$registryKeyValuePerceivedType" /d "$registryKeyValuePerceivedTypeValue" /f
reg.exe add "$registryShellKeyPath" /ve /d "Open with ATK" /f
reg.exe add "$registryCommandKeyPath" /ve /d "$registryCommandKeyValue" /f

Write-Host "Context menu entry added for .atk files."
Write-Host "You can now close this window by clicking any button."
