#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>


#include "argHeader.h"
#include "readFile.h"
#include "exitFailure.h"
#include "writeFile.h"
#include "findCwd.h"
#include "cryption.h"

using namespace std;

void readFile(string filePath, basicInfo* result){
    string fullPath = filePath;

    /* Checks if path contains string: ./ or .\ */
    if(filePath.substr(0, 2) == ".\\" || filePath.substr(0,2) == "./"){
        fullPath = findCwd(filePath);
    }
    /* Checks if given path exists*/
    if( !filesystem::exists(fullPath) ){
        cerr << fullPath << " Is not a valid path" << endl;
        exitfailure();
    }

    // Add path to result
    result->path = fullPath;

    /* New file */
    fstream newfile;

    // Holds value of the new pathfile
    string newPathToFile;


   /**
     * Reads file line by line
    */
    newfile.open(filePath, ios::in | ios::binary); // Open file using read operation

    // Make new path for new file
    // /old/path/name.atk
    // Changes .ext to atk

    // Get position of last '.'
    const int pos = fullPath.find_last_of(".");
    // !
    // ! Checks if file is not .atk file
    // !
    if (fullPath.substr(pos, fullPath.length()) != ".atk") {
        // Create new substring excluding the .ext part
        newPathToFile = fullPath.substr(0, pos);

        // Add .atk file extension
        newPathToFile = newPathToFile + ".atk";

        // Add newpath to result
        result->newPath = newPathToFile;

       // Initialize files header section with @param 0
       writeFile("" ,result, 0, 0);
    }
    else { // If .atk file
        // GET PREVIOUS FILE EXTENSION FROM THE FILE
        string prev;
        if(newfile.is_open()) {
            string line;

            while (getline(newfile, line)) { // Reads file contents line by line

                // ! No idea why _PASSWORD_ returns the line of _EXTENSION_
                // ! But it does...
                if (line.find("_PASSWORD_")) { // Find _EXTENSION_

                    // Decrypt the extension
                    std::vector<char32_t> newExtensionC;
                    string newExtensionS;

                    newExtensionC = deCrypt(line.substr(line.find_last_of("_") + 1, line.length()), result);

                    // Change extension to decrypt
                    for (char c : newExtensionC) {
                        newExtensionS += c;
                    }

                    prev = "." + newExtensionS;


                    prev = "." + line.substr(line.find_last_of("_") + 1, line.length());
                    break;
                }

                // Password here
                else {
                    cout << "PASSWORD IS HERE ::::: " << line << endl;
                }
            }
        }
        // HERE AS PLACEHOLDER
        newPathToFile = fullPath.substr(0, pos);
        newPathToFile = newPathToFile + prev;

        // Add newpath to result
        result->newPath = newPathToFile;
    }



    if (newfile.is_open()){   // Checks if file is open
        string line;
        string data;

        // !
        // ! Checks if file is .atk file
        // !
        if (fullPath.substr(pos, fullPath.length()) == ".atk") {
            while (getline(newfile, line)) { 
                // Reads file contents line by line
                // Write to the given file current line.
                //
                // STARTS STRAIGHT FROM DATA
                // DUE TO EARLIER READING    

                // Add the current line to data
                data += line + "\n";

            }
            newfile.close(); // Closes the file

            writeFile(data, result, 1, true);

        } 
        // !
        // ! If not .atk file
        // !
        else { 
            while(getline(newfile, line)){ 
                // Reads file contents line by line
                // Write to the given file current line.
                //
                // Add the current line to data
                data += line + "\n";
            }
            newfile.close(); // Closes the file

            // Write the data
            writeFile(data, result, 1, false);
        }

    } // End of newfile.open
}
