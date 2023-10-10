@echo off
set SourceFiles=src\args\*.cpp src\global\*.cpp src\fileHandling\*.cpp src\cryption\*.cpp main.cpp
set OutputFile=.\build\atk.exe

IF NOT EXIST .\build mkdir .\build

g++ -o "%OutputFile%" %SourceFiles%
