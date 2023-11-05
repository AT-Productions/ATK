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
$callDir = $args[0]
$mode = $args[1]



# Windows PATH Environment Variable Setup
#
# ---------------------------------------------------------------------
# Add the current directory to the PATH environment variable
# Check if folder $callDir is already in the path
# ! Adds path to build folder
$pathDir = "";
if($mode -like "manual"){
    $pathDir = "$callDir\Release"
} else {
    $pathDir = "$callDir"
}

Write-Host Adding current path to System Environmental Variables.
if($Env:PATH -notlike "*$pathDir*"){
    # TRUE, ADD TO PATH


    # Make oldPath and newPath variables
    $oldpath = (Get-ItemProperty -Path 'Registry::HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\Environment' -Name PATH).path
    $newpath = "$oldpath;$pathDir"
    
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

$newpathext = "$oldpathext;.ATK"

# Check if .ATK is already in the pathext
Write-Host Adding .ATK to PATHEXT.
if($Env:PATHEXT -notlike "*.ATK*"){
    # TRUE, ADD TO PATHEXT
    Set-ItemProperty -Path 'Registry::HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\Environment' -Name PATHEXT -Value $newpathext
    Write-Host Added .ATK to PATHEXT.
} else {
    # FALSE, DON'T ADD
    Write-Host .ATK already found in PATHEXT.
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

# Define the path to your custom icon
$iconPathExe = "$PSScriptRoot\atk-exe.ico"

# Define the path to your custom icon
$iconPath = "$PSScriptRoot\atk-ext.ico"

# Define the path to your "open_with_atk.cmd" script
$cmdScriptPath = "$PSScriptRoot\open_with_atk.cmd"


# Create registry entries
reg.exe add "$registryKeyPath" /v "$registryKeyValuePerceivedType" /d "$registryKeyValuePerceivedTypeValue" /f
reg.exe add "$registryShellKeyPath" /ve /d "Open with ATK" /f
reg.exe add "$registryCommandKeyPath" /ve /d "$cmdScriptPath `"%1`"" /f
# Context menu icon
reg.exe add "$registryShellKeyPath" /v "Icon" /d "$iconPathExe" /f
# Add position
# reg.exe add "$registryKeyPath" /v "Position" /d "Top" /f

# Add the DefaultIcon registry key with the path to your custom icon
reg.exe add "$registryKeyPath\DefaultIcon" /ve /d "$iconPath" /f


Write-Host "Context menu entry added for .atk files."
Write-Host "Context menu entry added for .atk files."

# Add gloval reged Crypt with ATK
$cryptCmd = "$PSScriptRoot\encrypt_with_atk.cmd"
reg.exe add "HKCR\*\shell\Encrypt with ATK" /ve /d "Encrypt with ATK" /f
reg.exe add "HKCR\*\shell\Encrypt with ATK\command" /ve /d "$cryptCmd `"%1`"" /f

# Context menu icon
reg.exe add "HKCR\*\shell\Encrypt with ATK" /v "Icon" /d "$iconPathExe" /f
# Add position
# reg.exe add "HKCR\*\shell\Encrypt with ATK" /v "Position" /d "Top" /f

Write-Host "Context menu icon added for all files."
Write-Host "Context menu entry added for all files."
Write-Host "Custom icon added for .atk files."



# $shortcutPath = "$callDir\open_with_atk.lnk"

# # Create a WScript Shell object
# $WshShell = New-Object -ComObject WScript.Shell

# # Create the shortcut
# $shortcut = $WshShell.CreateShortcut($shortcutPath)
# $shortcut.Arguments = "`"$cmdScriptPath`" `"%1`""
# $shortcut.IconLocation = $iconPath
# $shortcut.Save()

# Write-Host "Shortcut created with the specified icon."


# $shortcutPath = "$callDir\encrypt_with_atk.lnk"

# # Create a WScript Shell object
# $WshShell = New-Object -ComObject WScript.Shell

# # Create the shortcut
# $shortcut = $WshShell.CreateShortcut($shortcutPath)
# $shortcut.Arguments = "`"$cryptCmd`" `"%1`""
# $shortcut.IconLocation = "$PSScriptRoot\atk-exe.ico"
# $shortcut.Save()

# Write-Host "Shortcut created with the specified icon."

# Write-Host "Shortcut created in AppData Roaming folder."


# Refresh environmental variables
$Env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine")
Write-Host "Environmental variables refreshed"

Write-Host "Setup succesfull."