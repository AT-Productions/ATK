# Check if the script is running with administrator privileges
$isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")
if (-not $isAdmin) {
    Write-Host "You need to run this script as an administrator."
    Write-Host "Please right-click on the script and select 'Run as administrator.'"
    pause
    exit 1
}

# Adding the current directory to the PATH environment variable
$env:Path += ";$((Get-Item -Path '.' -ErrorAction SilentlyContinue).FullName)"

# Setting the PATHEXT environment variable
$env:PATHEXT += ";.atk"

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
