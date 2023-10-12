@echo off

:: Compiler: cywgin or msys bin folders in PATH is required.

:: Sourcefiles
set SourceFiles=.\ATK\*.cpp

:: Files output location
set OutputFile=.\build\atk.exe

:: Creates directory build if it does not exist
IF NOT EXIST .\build mkdir .\build

echo Starting compiler

:: Compile with g++
g++ -o "%OutputFile%" %SourceFiles%
