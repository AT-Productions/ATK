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


    newfile.open(filePath, ios::in); // Open file using read operation
    // Make new path for new file
    // /old/path/name.atk
    // Changes .ext to atk

    // Get position of last '.'
    int pos = fullPath.find_last_of(".");

    // Create new substring excluding the .ext part
    string newPathToFile = fullPath.substr(0, pos);
    cout << newPathToFile << endl;
    // Add .atk file extension
    newPathToFile = newPathToFile + ".atk";

   // Initialize files header section with @param 0
   writeFile("" ,result, 0, 0, newPathToFile);


    
    if (newfile.is_open()){   // Checks if file is open
        string line;
        // int i = 0;
        string data;
        while(getline(newfile, line)){ // Reads file contents line by line
            // Write to the given file current line. Send 1 to add blocks
            cout << line << endl;
            data += line + "\n";
            // i++
        }
        newfile.close(); // Closes the file

        writeFile(data, result, 1, 1, newPathToFile);
        cout << result << endl;
        cout << &result << endl;
        writeFile("]", result, 1, 1, newPathToFile);
    }
}

