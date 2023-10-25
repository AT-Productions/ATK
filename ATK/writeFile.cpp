#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include <vector>

#include <locale>

#include "argHeader.h"
#include "writeFile.h"
#include "cryption.h"
#include "exitFailure.h"

using namespace std;

void writeFile(string content = "", basicInfo* result = nullptr, int action = 1, bool decrypt = false) {
    // Do initialization with action0
    if (action == 0) {
        // Delete old file
        if (remove(result->newPath.c_str()) == 0) {}


        // Create new file or modify it
        ofstream newFile(result->newPath, std::ios::app | std::ios::binary);
        // Set the locale to UTF-8
        newFile.imbue(std::locale("en_US.UTF-8"));
        /**
         * ---------------------------------------------
         * Starts writing to new file
         *
         * cryptFunc("string");
        */

        // Crypted versions of password and file extension
        std::vector<char32_t> newPasswordC, newExtensionC;
        newPasswordC = crypt(result->password, result);
        newExtensionC = crypt(result->path.substr(result->path.find_last_of(".") + 1, result->path.length()), result);

        // String versions
        wstring newPasswordS;
        string newExtensionS;

        // Change password to crypt
        for (char32_t c : newPasswordC) {
            if (c <= std::numeric_limits<wchar_t>::max()) {
                wchar_t wc = static_cast<wchar_t>(c);
                newPasswordS += wc;
            }
            else {
                // Handle the case where a char32_t character cannot be represented as a wchar_t
                std::cerr << "Character cannot be converted to wchar_t without data loss." << std::endl;
                // You might want to decide what to do in this case
            }
        }
        
        // Change extension to crypt
        for (char32_t c : newExtensionC) {
            if (c <= std::numeric_limits<wchar_t>::max()) {
                wchar_t wc = static_cast<wchar_t>(c);
                newExtensionS += wc;
            }
            else {
                // Handle the case where a char32_t character cannot be represented as a wchar_t
                std::cerr << "Character cannot be converted to wchar_t without data loss." << std::endl;
                // You might want to decide what to do in this case
            }
        }


        // Adds the original file extension. Finds position of the last '.'
        //  and takes a substring from it to the end of the string


        newFile << "_PASSWORD_" << newPasswordS.c_str() << endl;
        //newFile << "_EXTENSION_" << newExtensionS << endl;
        newFile << "_EXTENSION_" << result->path.substr(result->path.find_last_of(".") + 1, result->path.length()) << endl;
        newFile.close();
    }

    // Make BLOCKS with action1
    if (action == 1) {
        ofstream newFile(result->newPath, std::ios::app | std::ios::binary);

        // Set the locale to UTF-8
        newFile.imbue(std::locale("en_US.UTF-8"));

        if (newFile.fail()) {
            cerr << "Error opening the file for writing." << endl;
            exitfailure();
        }

        std::vector<char32_t> results;

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

        for (char32_t c : results) {
            resultString += c;
        }
        newFile << resultString;

        // Close the file
        newFile.close();


        // Delete the previous file
        if (remove(result->path.c_str()) == 0) {}
    }
}