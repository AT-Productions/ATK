#include <iostream>
#include <map>
#include <string>

#include "argHeader.h"
#include "help.h"
#include "findFromArray.h"
#include "getVersion.h"
#include "exitFailure.h"

using namespace std;

void unexpected(string);
/**
 * Switch case, look what needs to be done.
*/
basicInfo* handleArgs(char** argv, int argc) {

    // All arg types for error checking
    const string argTypes[5] = {
        "t", "p", "s"
    };

    const int argTypesSize = sizeof(argTypes) / sizeof(argTypes[0]); // Size of argTypes Array

    basicInfo* result = new basicInfo; // Initialize result struct

    string currentArg = ""; // Initialize current argument
    string next = "";       // Initialize next argument



    for (int i = 1; i < argc; ++i){ /* Loop through args*/
        currentArg = argv[i]; // The current argument

        // Checks for --help
        if (currentArg == "--help") {

            // If it is found, consolelog longHelp message and exit
            cout << longHelp();
            exitfailure();
        }

        // Checks for --version or -v
        else if(currentArg == "-v" || currentArg == "--version"){

            // If it is found, consolelog getVersion message and exit
            cout << getVersion();
            exitfailure();
        }

        // TODO finish
        else if (currentArg == "-l" || currentArg == "--location") {
            cout << "Current location is " << endl;
            exitfailure();
        }


        if(i % 2 == 1){ // 
/**------------------------------------------------------------
             * Checks and saves the: - typed arguments
-------------------------------------------------------------*/

            // Put it to memory for next loop pass
            next = &currentArg[1];

            // If it is not a: - typed argument
            if (!findFromArray(argTypes, argTypesSize, next)) {

                // Call unexpected and exit the code
                unexpected(&currentArg[0]);
            }
            
        } else {
/**------------------------------------------------------------
             * Values for: - typed arguments
-------------------------------------------------------------*/


            if(next == "t"){ // Check for filetype
                result->type = currentArg[0];
            }

            else if(next == "p"){ // Checks for filepath
                // ! callerPath.cpp HERE !
                result->path = &currentArg[0];      
            }

            else if(next == "s"){ // Checks for password
                result->password = &currentArg[0];
            }
            else {
                unexpected(&currentArg[0]);
            }

        }
    }

    /* Check that the correct types have been given */
    if(result->path == "" || result->password == ""){
        cout << "Path or Password is not defined. " << shortHelp() << endl;
        /* Call exit failure */
        exitfailure();
    }
    if (result->type != "d" & result->type != "f") {
        cout << "Invalid type \"" << result->type << "\". " << shortHelp() << endl;
        /* Call exit failure */
        exitfailure();
    }
    
    
    // Return the basicInfo struct with the data
    return result;
}

/**
 * Function used to consolelog unexpected
 * arguments from the users
*/
void unexpected(string next){
    // Logs to console shortHelp and exits
    cout << next << " was unexpected." << endl << shortHelp();
    exitfailure();
}