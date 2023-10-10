#include <iostream>
#include <string>

/* CUSTOM HEADER FILE IMPORTS */
#include "include/argHeader.h"
#include "include/help.h"
#include "include/readFile.h"
#include "include/exitFailure.h"
#ifdef __linux__
#include <unistd.h>
#else
#include <direct.h>
#endif
using namespace std;

/**
 * https://learn.microsoft.com/en-us/previous-versions/windows/desktop/legacy/cc144169(v=vs.85)?redirectedfrom=MSDN
*/

/**
 * Startpoint
*/
int main(int argc, char *argv[]){
  // argv[argc-1] LAST ARGUMENT
  // argv[0] EXE NAME
  // ENTER ARGS WITH SPACES = "ABC DEF GEH"
  
  if( argc <= 1 ){ /* If there are no arguments, throw exit failure */ 
    cout << shortHelp() << endl;
    exitfailure();
  }
  // Does the basic stuff with args
  basicInfo* result = handleArgs(argv, argc);

  // CHECKS IF POINTER IS NULL
  if (result != nullptr) {

      // Read the file, function throws exitfailure if it doesn't exist
      readFile(result->path, result);
      
      // Access and print the data
      // cout << "Type: " << result->type << endl;
      // cout << "Path: " << result->path << endl;
      // cout << "Password: " << result->password << endl << endl;

      // DELETE FROM MEMORY
      delete result;

  } else { // IF NULL POINTER
      cout << "handleArgs returned a null pointer." << endl;
      return EXIT_FAILURE;
  }


  return 0;
}