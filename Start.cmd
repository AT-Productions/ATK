@echo off

:: "hkey_classes_root\atk\shell\" -Force
:: REGED
:: https://learn.microsoft.com/en-us/windows/win32/shell/context-menu-handlers?source=recommendations

ECHO Adding %cd% to the PATH environment variable

set PATH=%PATH%;%cd% /m & :: Adds current dir to env. vars


ECHO Setting PATHEXT environment variable

set PATHEXT=%PATHEXT%;.atk /m & :: Adds .atk to PATHEXT

ECHO Restart your command prompt

pause
