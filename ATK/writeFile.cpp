#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <locale>
#include <vector>
#include <codecvt>

#include "argHeader.h"
#include "writeFile.h"
#include "cryption.h"
#include "exitFailure.h"

using namespace std;
/**
 * Write to given file
 * @param pathToFile Path to the file
 * @param result Pointer to result struct
 * @param action Parameter that checks actions
 * @param decrypt true = File is going to be decrypted
 * @param newPathToFile Contains the new path.
*/
void writeFile(string content = "", basicInfo* result = nullptr, int action = 1, bool decrypt = false, string newPathToFile = "") {
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
        
        newFile /* << currentrow++ */ << "_PASSWORD_" << passwordHash(result) << endl;

        // Adds the original file extension. Finds position of the last '.' and takes a substring from it to the end of the string
        newFile /* << currentrow++ */ <<  "_EXTENSION_" << result->path.substr(result->path.find_last_of("."), result->path.length()) << endl;
        newFile /* << currentrow++ */ <<  "_START_" << endl;
        // newFile << "BLOCK0" << result->path.substr(pos, result->path.length()) << currentrow++ << " ENDROW " << endl; ;
    }
    

    // Make BLOCKS with action1
    if(action == 1){
        ofstream file(newPathToFile, std::ios::app | std::ios::binary);

        if (file.fail()) {
            cerr << "Error opening the file for writing." << endl;
            exitfailure();
        }
        /*
         https://stackoverflow.com/questions/23461499/decimal-to-unicode-char-in-c
        */

        // currentrow = 7 + blockInt;
        std::vector<char32_t> results;
        std::vector<wchar_t> newResults;
        std::string writeStr;
        std::vector<uint16_t> utf16;

        if (decrypt == true) {
            // Decrypt the contents and get the result vector
            results = deCrypt(content, result);
        }
        else {
            // Crypt the content and get the result vector
            results = crypt(content, result);
        }
        // Print the contents of the 'result' vector
        for (char32_t c : results) {
            if (c <= 0xFFFF) {
                // If the character is within the UTF-16 range
                utf16.push_back(static_cast<uint16_t>(c));
            }
            else {
                // HANDLE ERRORS
                // COMING SOON
            }
        }

        // Write the UTF-16 data to the file
        file.write(reinterpret_cast<char*>(utf16.data()), utf16.size() * sizeof(uint16_t));
        // Close the file
        file.close();
    }
}