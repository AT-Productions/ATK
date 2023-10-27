:: Only purpose is to move ATK.exe 
:: from \Release\ to \installation\
:: and make the installer and run it

@echo off

::
copy .\Release\ATK.exe .\installation\ /y /b

makensis.exe .\installation\script.nsi

.\installation\ATK-Installer.exe

echo DONE