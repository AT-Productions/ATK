#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include <vector>

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#pragma warning(disable : 4996)

#include <locale>
#include <codecvt>

#include "argHeader.h"
#include "writeFile.h"
#include "cryption.h"
#include "exitFailure.h"

using namespace std;

std::string convertChar16toUTF8(char16_t c) {
    if (c <= 0x7F) {
        // ASCII characters (0x00 to 0x7F) can be directly converted to UTF-8
        return { static_cast<char>(c) };
    }
    else if (c <= 0x07FF) {
        // 2-byte UTF-8 encoding for characters in the range 0x80 to 0x7FF
        std::string utf8;
        utf8 += static_cast<char>(0xC0 | (c >> 6));
        utf8 += static_cast<char>(0x80 | (c & 0x3F));
        return utf8;
    }
    else {
        // 3-byte UTF-8 encoding for characters outside the BMP
        std::string utf8;
        utf8 += static_cast<char>(0xE0 | (c >> 12));
        utf8 += static_cast<char>(0x80 | ((c >> 6) & 0x3F));
        utf8 += static_cast<char>(0x80 | (c & 0x3F));
        return utf8;
    }
}

void writeFile(string content = "", basicInfo* result = nullptr, int action = 1, bool decrypt = false) {
    // Do initialization with action0
    // Delete old file
    if (action == 0) {
        if(remove(result->newPath.c_str()) == 0) {}
    }
    // Create new file or modify it
    ofstream newFile(result->newPath, std::ios::app | std::ios::binary);

    std::locale::global(std::locale("zh_CN.UTF-8"));

    newFile.imbue(std::locale("zh_CN.UTF-8"));

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
        wstring newPasswordS;
        string newExtensionS;

        // Change password to crypt
        for (char16_t c : newPasswordC) {
            if (c <= std::numeric_limits<wchar_t>::max()) {
                wchar_t wc = static_cast<wchar_t>(c);
                newPasswordS += wc;
            }
            else {
                // Handle the case where a char16_t character cannot be represented as a wchar_t
                std::cerr << "Character cannot be converted to wchar_t without data loss." << std::endl;
                // You might want to decide what to do in this case
            }
        }
        
        // Change extension to crypt
        for (char16_t c : newExtensionC) {
            if (c <= std::numeric_limits<wchar_t>::max()) {
                wchar_t wc = static_cast<wchar_t>(c);
                newExtensionS += wc;
            }
            else {
                // Handle the case where a char16_t character cannot be represented as a wchar_t
                std::cerr << "Character cannot be converted to wchar_t without data loss." << std::endl;
                // You might want to decide what to do in this case
            }
        }


        // Adds the original file extension. Finds position of the last '.'
        //  and takes a substring from it to the end of the string


        newFile << "_PASSWORD_" << newPasswordS.c_str() << endl;
        //newFile << "_EXTENSION_" << newExtensionS << endl;

        // ! TEMP
        newFile << "_EXTENSION_" << result->path.substr(result->path.find_last_of(".") + 1, result->path.length()) << endl;
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


        for (char16_t c : results) {
            newFile << static_cast<char>(c);
        }


        // Close the file
        newFile.close();


        // Delete the previous file
        if (remove(result->path.c_str()) == 0) {}
    }
}