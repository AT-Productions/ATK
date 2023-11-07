#include <iostream>
#include <string>

#include "argHeader.h"
#include "help.h"
#include "readFile.h"
#include "exitFailure.h"
#include "getVersion.h"
#include "cryption.h"

#ifdef __linux__
#include <unistd.h>
#else
#include <direct.h>
#endif
using namespace std;

/* 
    if password = 123 ||213 || 321 || 312 and extension has c it will turn to d
    !lol
*/

int main(int argc, char* argv[]){
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

        cypherAmount(result);

        // Read the file, function throws exitfailure if it doesn't exist
        readFile(result->path, result);

        // DELETE FROM MEMORY
        delete result;
        result = nullptr;
    }
    else { // IF NULL POINTER
        cout << "handleArgs returned a null pointer." << endl;
        exitfailure();
    }


    return 0;
}