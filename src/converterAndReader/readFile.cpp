#include <string>
#include <iostream>
#include <fstream>
#include <direct.h>
#include <filesystem>

#include "../../include/argHeader.h"
#include "../../include/readFile.h"
#include "../../include/exitFailure.h"

using namespace std;
/**
 * Reads given file
 * @param filepath path to the given file which will be read by this function
*/
void readFile(string filePath, basicInfo* result){
    string fullPath = filePath;
    
    /* Checks if path contains string: cwd (current working directory) */
    if(fullPath.find(".") != string::npos){

        /* Create character array with length of maximum windows path length */
        char buffer[_MAX_PATH];

        // Checks for cwd
        if (_getcwd(buffer, sizeof(buffer)) != nullptr) {
            /* Build the path */

            // get the filename
            string fileName = "\\" + fullPath.substr(2, fullPath.length());

            // Add the buffer (call location) and fileName to create the fullpath
            fullPath = buffer + fileName;
        } else {
            perror("_getcwd");
            exitfailure();
        }
    }
    

    /* Checks if given path exists*/
    if( !filesystem::exists(fullPath) ){
        cout << fullPath << " Is invalid" << endl;
        exitfailure();
    }

    // Add path to result
    result->path = fullPath;

    // Delete pointer to result
    delete result;



    /**
     * ------------------------------------
     * 
    New file */
    fstream newfile;
   /**
     * Reads file line by line
    */

    newfile.open(fullPath,ios::in); // Open file using read operation
    if (newfile.is_open()){   // Checks if file is open
        string line;
        while(getline(newfile, line)){ // Reads file contents line by line
            cout << line << endl; 
        }
        newfile.close(); // Closes the file
    }

}

