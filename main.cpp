#include <iostream>
#include <string>
#include <stdlib.h> // EXIT_FAILURE

#include "include/argHeader.h"
#include "include/help.h"

using namespace std;

/**
 * https://learn.microsoft.com/en-us/previous-versions/windows/desktop/legacy/cc144169(v=vs.85)?redirectedfrom=MSDN
*/

/**
 * Startpoint
 * 
 * ! ADD DIRECTORIES LATER
*/
int main(int argc, char *argv[]){
  // argv[argc-1] LAST ARGUMENT
  // argv[0] EXE NAME
  // ENTER ARGS WITH SPACES = "ABC DEF GEH"

  
  if( argc <= 1 ){ /* If there are no arguments, throw exit failure*/ 
    cout << shortHelp() << endl;
    return EXIT_FAILURE;
  }
  // Does the basic stuff with args
  // ! REMEMBER TO CHECK basicInfo.password != ""; OR SOMETHING LIKE THAT
  basicInfo* result = handleArgs(argv, argc);
  // CHECK IF POINTER IS NULL
  if (result != nullptr) {
      // Access and print the data
      cout << "Type: " << result->type << endl;
      cout << "Path: " << result->path << endl;
      cout << "Password: " << result->password << endl;
      
      // DELETE FROM MEMORY
      delete result;
  } else { // IF NULL POINTER
      cout << "handleArgs returned a null pointer." << endl;
      return EXIT_FAILURE;
  }


  return 0;
}