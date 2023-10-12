#include <string>
#include <iostream>
#include <fstream>

#include <filesystem>

#include "argHeader.h"
#include "readFile.h"
#include "exitFailure.h"
#include "writeFile.h"
#include "findCwd.h"

using namespace std;
/**
 * Reads given file
 * @param filepath path to the given file which will be read by this function
*/
void readFile(string filePath, basicInfo* result){
    string fullPath = filePath;
    
    /* Checks if path contains string: ./ or .\ */
    if(filePath.substr(0, 2) == ".\\" || filePath.substr(0,2) == "./"){
        fullPath = findCwd(filePath);
    }
    

    /* Checks if given path exists*/
    if( !filesystem::exists(fullPath) ){
        cerr << fullPath << " Is invalid" << endl;
        exitfailure();
    }

    // Add path to result
    result->path = fullPath;

    /**
     * ------------------------------------
     * 
    New file */
    fstream newfile;

    // Holds value of the new pathfile
    string newPathToFile;
   /**
     * Reads file line by line
    */


    newfile.open(filePath, ios::in); // Open file using read operation
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

       // Initialize files header section with @param 0
       writeFile("" ,result, 0, 0, newPathToFile);
    }
    else {
        // TODO GET PREVIOUS FILE EXTENSION FROM THE FILE!

        // HERE AS PLACEHOLDER
        newPathToFile = fullPath.substr(0, pos);
        newPathToFile = newPathToFile + ".txt";
    }

    
    if (newfile.is_open()){   // Checks if file is open
        string line;
        string data;
        int i = 0;


        // !
        // ! Checks if file is .atk file
        // !
        if (fullPath.substr(pos, fullPath.length()) == ".atk") {
            // First 3 rows = Headers. after that file content.
            while (getline(newfile, line)) { // Reads file contents line by line
                // Write to the given file current line.

                // First row = don't make new row
                if (i < 3) {
                    // HEADERS HERE
                    // TODO HANDLE THESE
                }
                else {
                    // Everything else here
                    data += line;
                }
                // Add the current line to data
                i++;
            }
            newfile.close(); // Closes the file

            writeFile(data, result, 1, true, newPathToFile);
        } else { // If not .atk file
            while(getline(newfile, line)){ // Reads file contents line by line
                // Write to the given file current line.

                // First row = don't make new row
                if (i == 0) {
                    data += line;
                } else {
                    data += "\n" + line;
                }
                // Add the current line to data
                i++;
            }

            newfile.close(); // Closes the file

            // Write the data
            writeFile(data, result, 1, false, newPathToFile);

        }

       
        
        // End files block with ]
        // ! Moved "temporarily" to writeFile.cpp
        // writeFile("]", result, 1, 1, newPathToFile);

    } // End of newfile.open

}
