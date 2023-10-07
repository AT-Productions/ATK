#include <iostream>
#include <iostream>
#include "../include/argHeader.h"

using namespace std;

/**
 * EXAMPLE:
 * () means it is not obligatory
 * kml TYPE type PATH path (PASS password)
 * 
 * MORE EXAMPLES
 * kml TYPE dir PATH cwd PASS 1234
 * kml TYPE file PATH "C:\path\to\file"
 * 
 * --ARG TYPES:
 * --help = RETURNS HELP MESSAGE
 * --v / --version = RETURNS CURRENT VERSION
 * --location = RETURNS .EXE LOCATION OF THE kml.exe
 * 
*/
void handleArgs(string argument) {
    cout << argument << "\n";
}

