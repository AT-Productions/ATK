@echo off
SET WiX="%ProgramFiles(x86)%\WiX Toolset v3.11\bin\"

%WiX%candle.exe -nologo -out .\MyAppInstaller.wixobj .\Product.wxs
%WiX%light.exe -nologo -out .\MyAppInstaller.msi .\MyAppInstaller.wixob