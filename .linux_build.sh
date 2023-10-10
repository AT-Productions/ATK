#!/bin/bash
output=./build/atk
files="src/args/*.cpp src/global/*.cpp src/fileHandling/*.cpp src/cryption/*.cpp main.cpp"

# Check if build folder exists
if [ ! -d "./build" ]; then
    echo "Creating folder 'build'"
    mkdir build
fi

g++ -o "$output" $files
