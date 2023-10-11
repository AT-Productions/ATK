#!/bin/bash
output=./build/atk
files="ATK/*.cpp"

# Check if build folder exists
if [ ! -d "./build" ]; then
    echo "Creating folder 'build'"
    mkdir build
fi

g++ -O3 -o "$output" $files -ggdb -g3
