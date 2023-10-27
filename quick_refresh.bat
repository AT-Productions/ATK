:: Only purpose is to move ATK.exe 
:: from \Release\ to \installation\
:: and make the installer and run it

@echo off

:: Copy from release to installation
copy .\Release\ATK.exe .\installation\ /y /b

:: Run compile script
makensis.exe .\installation\script.nsi

:: Run compiled executable
.\installation\ATK-Installer.exe

echo DONE