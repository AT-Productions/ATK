@echo off
set CommonCompilerFlags=-MTd -nologo -fp:fast -fp:except- -Gm- -GR- -EHa- -Zo -Od -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4505 -wd4127 -DHANDMADE_INTERNAL=1 -DHANDMADE_SLOW=1 -DHANDMADE_WIN32=1 -FC -Z7
set CommonLinkerFlags=-incremental:no -opt:ref user32.lib gdi32.lib winmm.lib
set "IncludePath=E:\Visual Studio\2022\VC\Tools\MSVC\14.16.27023\include"

IF NOT EXIST .\build mkdir .\build
pushd .\build

REM 64-bit build
del *.pdb > NUL 2> NUL
echo WAITING FOR PDB > lock.tmp
cl %CommonCompilerFlags% /I "%IncludePath%" /Fe:myprogram.exe .\ATK\main.cpp
del lock.tmp

popd
