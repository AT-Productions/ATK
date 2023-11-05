# Clear the icon cache
& "C:\Windows\System32\ie4uinit.exe" -ClearIconCache

# Kill the Explorer process
Stop-Process -Name explorer -Force

# Delete the IconCache.db file
$iconCachePath = [System.IO.Path]::Combine($env:LOCALAPPDATA, 'IconCache.db')
Remove-Item -Path $iconCachePath -Force -ErrorAction SilentlyContinue

Write-Host "Icon cache resetted. Restarting explorer"

# Restart the Explorer process
Start-Process explorer.exe

Write-Host "explorer.exe restarted."