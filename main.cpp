#include <iostream>
#include <string>
#include <stdlib.h> // EXIT_FAILURE
#include "include/argHeader.h"

using namespace std;

/**
 * https://learn.microsoft.com/en-us/previous-versions/windows/desktop/legacy/cc144169(v=vs.85)?redirectedfrom=MSDN
 * g++ -I./include -o kml.exe main.cpp
*/

/**
 * Startpoint
*/
int main(int argc, char *argv[]){
  // argv[argc-1] LAST ARGUMENT
  // argv[0] EXE NAME
  // ENTER ARGS WITH SPACES = "ABC DEF GEH"

  
  if( argc <= 1 ){ /* If there are no arguments, throw exit failure*/ 
    cout << "For help, type kml --help \n";
    return EXIT_FAILURE;
  }

  for (int i = 1; i < argc; ++i){ /* Loop through args*/
    handleArgs(argv[i]);
  }

    return 0;
}