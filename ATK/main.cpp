#include <iostream>
#include <string>

/* CUSTOM HEADER FILE IMPORTS */
#include "argHeader.h"
#include "help.h"
#include "readFile.h"
#include "exitFailure.h"
#include "getVersion.h"
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
int main(int argc, char* argv[]) {
    // argv[argc-1] LAST ARGUMENT
    // argv[0] EXE NAME
    // ENTER ARGS WITH SPACES = "ABC DEF GEH"

    /* If there are no arguments, throw exit failure */
    if (argc <= 1) { 
        cout << getVersion();
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
        result = nullptr;
    }
    else { // IF NULL POINTER
        cout << "handleArgs returned a null pointer." << endl;
       return EXIT_FAILURE;
    }


    return 0;
}