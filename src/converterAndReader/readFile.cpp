#include <string>
#include <iostream>
#include <fstream>

#include "../../include/readFile.h"
#include "../../include/exitFailure.h"

using namespace std;
/**
 * Reads given file
 * @param filepath path to the given file which will be read by this function
*/
void readFile(string filePath){
    // New file
    fstream newfile;
    /**
     * Reads file line by line
    */

    newfile.open(filePath,ios::in); // Open file using read operation
    if (newfile.is_open()){   // Checks if file is open
        string line;
        while(getline(newfile, line)){ // Reads file contents line by line
            /**
             * ! Read logic here !
            */

            cout << line << endl; 
        }
        newfile.close(); // Closes the file
    }

}

