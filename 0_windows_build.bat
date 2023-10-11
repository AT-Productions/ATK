@echo off

:: Compiler, cywgin or msys bin folders in PATH is required.

:: Sourcefiles
set SourceFiles=src\args\*.cpp src\global\*.cpp src\fileHandling\*.cpp src\cryption\*.cpp main.cpp

:: Files output location
set OutputFile=.\build\atk.exe

:: Creates directory build if it does not exist
IF NOT EXIST .\build mkdir .\build

:: Compile with g++
g++ -o "%OutputFile%" %SourceFiles%
