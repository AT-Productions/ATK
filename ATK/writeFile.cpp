#include <fstream>
#include <string>
#include <string>
#include <vector>
#include <iostream>

#include <locale>

#include "argHeader.h"
#include "writeFile.h"
#include "cryption.h"
#include "exitFailure.h"

using namespace std;

void writeFile(string content = "", basicInfo* result = nullptr, int action = 1, bool decrypt = false) {
    // Do initialization with action0
    // Delete old file
    if (action == 0) {
        if(remove(result->newPath.c_str()) == 0) {}
    }
    // Create new file or modify it
    ofstream newFile(result->newPath, std::ios::app | std::ios::binary);

    // Set chinese utf as locale
    std::locale::global(std::locale("en_US.UTF-8"));
    //newFile.imbue(std::locale("zh_CN.UTF-8"));

    if (action == 0) {
        /**
         * Starts writing to new file
         */

        // Crypted versions of password and file extension
        std::vector<char16_t> newPasswordC, newExtensionC;

        newPasswordC = crypt(result->password, result);
        newExtensionC = crypt(
            result->path.substr(
                result->path.find_last_of(".") + 1,
                result->path.length()
            ), result
        );
        // String versions
        string newPasswordS;
        string newExtensionS;

        // Change password to crypt
        for (char16_t c : newPasswordC) {
            newPasswordS += static_cast<char>(c);
        }
        
        // Change extension to crypt
        for (char16_t c : newExtensionC) {
            newExtensionS += static_cast<char>(c);
        }

        newFile << newPasswordS << endl;
        //newFile << newExtensionS << endl;

        // ! TEMP
        // Adds the original file extension. Finds position of the last '.'
        // and takes a substring from it to the end of the string
        //newFile << result->password << endl;
        newFile << result->path.substr(result->path.find_last_of(".") + 1, result->path.length()) << endl;
        newFile.close();
    }

    // Make BLOCKS with action1
    if (action == 1) {

        if (newFile.fail()) {
            cerr << "Error opening the file for writing." << endl;
            exitfailure();
        }

        std::vector<char16_t> results;

        /* DECRYPT THE FILE */
        if (decrypt == true) {
            // Decrypt the contents and get the result vector
            results = deCrypt(content, result);
        }

        /*CRYPT THE FILE*/
        else {
            // Crypt the content and get the result vector
            results = crypt(content, result);
        }

        // Create an empty string to store the result
        std::string resultString;

        // Write the results to the file
        for (char16_t c : results) {

            // On write turn to char
            newFile << static_cast<char>(c);
        }


        // Close the file
        newFile.close();


        // Delete the previous file
        if (remove(result->path.c_str()) == 0) {}
    }
}