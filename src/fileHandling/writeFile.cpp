#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <cstdlib>

#include "../../include/argHeader.h"
#include "../../include/writeFile.h"
#include "../../include/cryption.h"
#include "../../include/exitFailure.h"

using namespace std;
/**
 * Write to given file
 * @param pathToFile Path to the file
 * @param result Pointer to result struct
 * @param action Parameter that checks actions
*/
void writeFile(string content, basicInfo* result, int action, int blockInt){
    cout << content << " " << action << " " << blockInt << endl;
    fstream newfile;
    int currentrow = 0;
    // Make new path for new file
    // /old/path/name.atk
    // Changes .ext to atk

    // Get position of last '.'
    int pos = result->path.find_last_of(".");

    // Create new substring excluding the .ext part
    string newPathToFile = result->path.substr(0, pos);

    // Add .atk file extension
    newPathToFile = newPathToFile + ".atk";

    // Do initialization with action0
    if(action == 0){
        // Create new file or modify it

        // Delete old file
        remove(newPathToFile.c_str());

        // Open in append mode
        ofstream newFile(newPathToFile, ios::app);
        
        /**
         * ---------------------------------------------
         * Starts writing to new file
         * 
         * cryptFunc("string");
        */
        newFile /* << currentrow++ */ << "{" << endl; 
        newFile /* << currentrow++ */ << "_PASSWORD_" << result->password << endl;
        newFile /* << currentrow++ */ <<  "_EXTENSION_" << result->path.substr(pos, result->path.length()) << endl;
        newFile /* << currentrow++ */ <<  "}" << endl;
        newFile /* << currentrow++ */ <<  "[" << endl;
        // newFile << "BLOCK0" << result->path.substr(pos, result->path.length()) << currentrow++ << " ENDROW " << endl; ;
    }
    

    // Make BLOCKS with action1
    if(action == 1){
        ofstream file(newPathToFile, ios::app);
        if (file.fail()) {
            cerr << "Error opening the file for writing." << endl;
            exitfailure();
        }
        currentrow = 7 + blockInt;
        cout << "content" << endl;
        // file /* << currentrow */ << content << endl;
        file << content << endl;
    }
    // Delete pointer
    delete result;

    // Save file contents
}