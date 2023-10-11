#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <cstdlib>

#include "argHeader.h"
#include "writeFile.h"
// #include "cryption.h"
#include "exitFailure.h"

string test();

using namespace std;
/**
 * Write to given file
 * @param pathToFile Path to the file
 * @param result Pointer to result struct
 * @param action Parameter that checks actions
*/
void writeFile(string content = "", basicInfo* result = nullptr, int action = 1, int blockInt = 0, string newPathToFile = "") {
    //if (result == nullptr) {
    //    cout << "result was null" << endl;
    //    exitfailure();
    //}
    //basicInfo* result = new basicInfo;
    cout << content << " " << action << " " << blockInt << endl;
    fstream newfile;
    int currentrow = 0;

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
        newFile /* << currentrow++ */ <<  "_EXTENSION_" << newPathToFile.substr(newPathToFile.find_last_of("."), newPathToFile.length()) << endl;
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
        // currentrow = 7 + blockInt;
        // cout << "content" << endl;
        // file /* << currentrow */ << content << endl;
        cout << content << endl;
        file << content << endl;
    }
}
/*
#include <iomanip>
#include <iostream>
#include <limits>

#include <numbers>
string stoh(string const& in)
{
    ostringstream os;

    for (unsigned char const& c : in)
    {
        os << hex << setprecision(2) << setw(2)
            << setfill('0') << static_cast<int>(c);
    }

    return os.str();
}
*/