#include <fstream>
#include <string>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip> 
#include <locale>

#include "argHeader.h"
#include "writeFile.h"
#include "cryption.h"
#include "exitFailure.h"

using namespace std;

void writeFile(std::vector<unsigned char> content, basicInfo* result = nullptr, int action = 1, bool decrypt = false) {
    // Do initialization with action0

    // Delete old file
    if (action == 0) {
        if(remove(result->newPath.c_str()) == 0) {}
    }
    ofstream newFile(result->newPath, std::ios::app | std::ios::binary);

    // Create new file or modify it

    // Set chinese utf as locale
    std::locale::global(std::locale("en_US.UTF-8"));
    //newFile.imbue(std::locale("zh_CN.UTF-8"));

    if (action == 0) {
        /**
         * Starts writing to new file
         */

        // Crypted versions of password and file extension
        std::vector<unsigned char> newPasswordC, newExtensionC;


        std::vector<unsigned char> newPasswordCVector, newExtensionCVector;


        // Turn password and extension to unsigned char vectors:

        // EXT
        for (char c : result->path.substr(result->path.find_last_of(".") + 1)) {
            // Push value to vector as unsigned char
            int value = static_cast<int>(static_cast<unsigned char>(c));
            newExtensionCVector.push_back(value);
        }

        // Password
        for (char c : result->password) {
            // Push value to vector as unsigned char
            int value = static_cast<int>(static_cast<unsigned char>(c));
            newPasswordCVector.push_back(value);
        }


        int secPos = result->path.find_last_of("\\");

        string newStringMem = result->path.substr(secPos + 1);
        // If it has a . in it
        if (newStringMem.find_last_of(".") != -1) {
            // Use .
            newExtensionC = crypt(
                newExtensionCVector, result
            );

        }
        else {
            // Don't use .
            newExtensionC = { 20 };
        }

        newPasswordC = crypt(newPasswordCVector, result);
        

        // String versions
        string newPasswordS;
        string newExtensionS;

        // Change password to crypt
        for (unsigned char c : newPasswordC) {
            newPasswordS += static_cast<char>(c);
        }
        
        // Change extension to crypt
        for (unsigned char c : newExtensionC) {
            newExtensionS += static_cast<char>(c);
        }

        // Writes password and extension. below is seperator
        result->header = newPasswordS + "c?^ | ^?c" + newExtensionS + "\n";
    }

    // Make BLOCKS with action1
    if (action == 1) {
        if (newFile.fail()) {
            cerr << "Error opening the file for writing." << endl;
            exitfailure();
        }

        std::vector<unsigned char> results;

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
        resultString = result->header;
        // Write the results to the file
        
        std::string resultString2(results.begin(), results.end());
        resultString += resultString2;
       newFile << resultString;


        // Close the file
        newFile.close();

        // Delete the previous file
        if (remove(result->path.c_str()) == 0) {}
    }
}