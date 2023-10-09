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
# Adding the current directory to the PATH environment variable
Write-Host Adding the current directory ($callDir) to the PATH environment variable.
$oldpath = (Get-ItemProperty -Path 'Registry::HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\Environment' -Name PATH).path
$newpath = "$oldpath;$callDir"

# TODO Check if folder $callDir is already in the path
if($oldPath -notcontains $callDir){
    Set-ItemProperty -Path 'Registry::HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\Environment' -Name PATH -Value $newpath
} else {
    Write-Host $callDir is already in system PATH
}

# ---------------------------------------------------------------------

# Windows PATHEXT Environmental Variable Setup
#
# ---------------------------------------------------------------------
# Setting the PATHEXT environment variable
Write-Host Adding .atk to the PATHEXT environment variable `n.
$oldpathext = (Get-ItemProperty -Path 'Registry::HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\Environment' -Name PATHEXT).pathext

$newpathext = "$oldpathext;.atk"

# TODO Check if .atk is already in the pathext

Set-ItemProperty -Path 'Registry::HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\Environment' -Name PATHEXT -Value $newpathext
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
Write-Host "You can now close this window."
