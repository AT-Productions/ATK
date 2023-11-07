#include <iostream>
#include <map>
#include <string>

#include "argHeader.h"
#include "help.h"
#include "findFromArray.h"
#include "getVersion.h"
#include "exitFailure.h"
#include "deviceId.h"

using namespace std;

void unexpected(string);
bool testType(basicInfo* result);

basicInfo* handleArgs(char** argv, int argc) {
    bool nextArg = false;
    int j = 0;

    // All arg types for error checking, minus first char
    const string argTypes[8] = {
        "t", "p", "k", "s", "-type", "-path", "-key", "-safe"
    };

    const int argTypesSize = sizeof(argTypes) / sizeof(argTypes[0]); // Size of argTypes Array

    basicInfo* result = new basicInfo; // Initialize result struct

    string currentArg = ""; // Initialize current argument
    string next = "";       // Initialize next argument

    for (int i = 1; i < argc; ++i){ /* Loop through args*/
        currentArg = argv[i]; // The current argument
        if (nextArg && i == argc) {
            break;
        }
        // Checks for --help
        if (currentArg == "--help" || currentArg == "-h") {

            // If it is found, consolelog longHelp message and exit
            cout << longHelp();
            exitfailure();
        }

        // Checks for --version or -v
        else if (currentArg == "-v" || currentArg == "--version" || currentArg == "--v") {

            // If it is found, consolelog getVersion message and exit
            cout << getVersion();
            exitfailure();
        }

        // Returns the location
        else if (currentArg == "-l" || currentArg == "--location") {
            cout << "Current location is " << argv[0] << endl;
            exitfailure();
        }
             

        if( nextArg == false ? i % 2 == 1 : j % 2 == 1){ // Every other is next if -s spotted, use j
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

            // If argument safe has been used
            if (next == "s" || next == "-safe") {
                cout << "Argument: SAFE used. Use this argument at your own risk! Type y to continue, n to exit program." << endl;
                std::string answer;
                while (true) {
					cin >> answer;
                    if (answer == "y") {
						break;
                    }
                    else if (answer == "n") {
                        cout << "Stopped by user." << endl;
                        exitfailure();
                    }
                    else {
						cout << "Type y to continue, n to exit program." << endl;
					}
				}

                nextArg = true;
                result->safe = true;
                deviceId(result);
                
            }

        } else {
/**------------------------------------------------------------
             * Values for: - typed arguments
-------------------------------------------------------------*/
            if (next == "t" || next == "-type") { // Check for filetype
                result->type = &currentArg[0];
            }

            else if(next == "p" || next == "-path"){ // Checks for filepath
                result->path = &currentArg[0]; 
            }

            else if(next == "k" || next == "-key"){ // Checks for password
                result->password = &currentArg[0];
            }

            else {
                unexpected(&currentArg[0]);
            }

        }

        j++;
    }

    /* Check that the correct types have been given */
    if(result->password == ""){
        cout << "Key is not defined. " << shortHelp() << endl;
        /* Call exit failure */
        exitfailure();
    }
    if(result->path == ""){
        cout << "Path is not defined. " << shortHelp() << endl;
        /* Call exit failure */
        exitfailure();
    }

    if (testType(result)) {
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

bool testType(basicInfo* result) {
    // Allow the use of f and d
    if (result->type == "dir" || result->type == "file" || result->type == "d" || result->type == "f") {
        return false;
    }
    else {
        return true;
    }

}