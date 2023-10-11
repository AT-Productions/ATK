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
    cout << filePath.substr(0, 2) << endl;
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
   /**
     * Reads file line by line
    */

   // Initialize files header section with @param 0
   writeFile("" ,result, 0, 0);

    newfile.open(filePath,ios::in); // Open file using read operation
    if (newfile.is_open()){   // Checks if file is open
        string line;
        // int i = 0;

        while(getline(newfile, line)){ // Reads file contents line by line
            // Write to the given file current line. Send 1 to add blocks
            cout << line << endl;
            writeFile(line, result, 1, 1);
            // i++
        }
        writeFile("]", result, 1, 1);
        newfile.close(); // Closes the file
    }
    // Delete pointer to result
    delete result;

}

