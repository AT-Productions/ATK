#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <iomanip> 
#include <algorithm>

#include "help.h"
#include "argHeader.h"
#include "readFile.h"
#include "exitFailure.h"
#include "writeFile.h"
#include "findCwd.h"
#include "exitFailure.h"
#include "deviceId.h"
#include "cryption.h"

namespace fs = std::filesystem;
using namespace std;

void readFile(string filePath, basicInfo* result){
    string fullPath = filePath;

    /* Checks if path contains string: ./ or .\ */
    if(filePath.substr(0, 2) == ".\\" || filePath.substr(0,2) == "./"){
        fullPath = findCwd(filePath);
    }
    /* Checks if given path exists*/
    if( !filesystem::exists(fullPath) ){
        cerr << "Path is not valid" << endl;
        exitfailure();
    }

    

    // Check if filepath and type provided are correct
    std::error_code ec;
    if (fs::is_directory(fullPath, ec) && (result->type == "f" || result->type == "file")) {
        // Process a directory.
        cout << fullPath << " is a directory. " << shortHelp() << endl;
        exitfailure();
    }
    if (ec) {
        std::cerr << "Error in is_directory: " << ec.message();
    }
    if (fs::is_regular_file(fullPath, ec) && (result->type == "d" || result->type == "dir")) {
        // Process a regular file.
        cout << fullPath << " is a file. " << shortHelp() << endl;
        exitfailure();
    }
    if (ec) {
        std::cerr << "Error in is_regular_file: " << ec.message();
    }


    // Add path to result
    result->path = fullPath;

    /* New file */
    ifstream newfile(filePath, ios::in | ios::binary); // Open file using read operation;

    // Holds value of the new pathfile
    string newPathToFile;


    // Make new path for new file
    // /old/path/name.atk
    // Changes .ext to atk

    // Get position of last '.'
    int pos = fullPath.find_last_of(".");
    if (pos == std::string::npos) {
        pos += 1;
    }
    // !
    // ! Checks if file is not .atk file
    // ! 
    // ! Initialize fileheader
    // !
    if (fullPath.substr(pos, fullPath.length()) != ".atk") {
        // Create new substring excluding the .ext part
        
        // Get position of last \-character

        int secPos = fullPath.find_last_of("\\");

        string newStringMem = fullPath.substr(secPos + 1);
        // If it has a . in it
        if (newStringMem.find_last_of(".") != -1) {
            // Get part excluding .ext part
            newPathToFile = fullPath.substr(0, pos);

            // Add .atk file extension
            newPathToFile = newPathToFile + ".atk";
        }
        else {
            // Add .atk file extension
            newPathToFile = fullPath + ".atk";
        }

        // Add newpath to result
        result->newPath = newPathToFile;

        // Initialize files header section with @param 0
        std::vector<unsigned char>emptyVector = {};
        writeFile(emptyVector, result, 0, false);
        
    }

    else {
        // If .atk file
        // CHECK PASSWORD
        // GET PREVIOUS FILE EXTENSION FROM THE FILE
        string prev;
        if (newfile.is_open()) {
            string line;

            // Reads file contents line by line
            // Reads only password and file extension
            getline(newfile, line);

            // Position of separator
            string toFind = "41adc_c?^ | ^?cd-cgga";
            int separator = line.find(toFind);

            // PASSWORD-------------------------------------------------
            // Reads and decrypts password
            // If they aren't equal, throw error on console

            // Initialize variables
            string passwordString;
            vector<unsigned char> newPasswordC;
            vector<unsigned char> newPasswordCVector;

            // MEMORY
            std::string memF = "3hzk233dr198_DATA011kpp253";
            std::string memF_ = "kl_STM-pfge9132zbag91_META0312";
            std::string memF_2 = "w01|_DATAMSTRT_##+1ld13";

            int startPos1 = line.find("3hzk233dr198_DATA011kpp253");
            if (startPos1 != std::string::npos && separator != string::npos) {
                // Turn to integers
                result->elength = std::stoi(line.substr(0, startPos1));
                result->plength = std::stoi(line.substr(startPos1 + memF.length(), line.find(memF_)));
                result->dlength = std::stoi(line.substr(line.find(memF_2) + memF_2.length(), line.length()));
            }
            else {
                cerr << "Error reading file" << endl;
                exitfailure();
            }

            // Get password
            string extractedSubstring = line.substr(line.find(memF_) + memF_.length(), separator - (line.find(memF_) + memF_.length()));
            //cout << extractedSubstring << endl;
            // Turn password to vector
            for (char c : extractedSubstring) {
                // Push value to vector as unsigned char
                int value = static_cast<int>(static_cast<unsigned char>(c));
                newPasswordCVector.push_back(value);
            }


            // Contains vector holding the characters

            newPasswordC = deCrypt(newPasswordCVector, result, 0);

            // Check for \r\n
            for (unsigned char& c : newPasswordC) {
                if (static_cast<int>(c) == 14 || static_cast<int>(c) == 11) { // If char is 13 or 10 \r\n
                    // remove 1
                    c = static_cast<unsigned char>(static_cast<int>(c) - 1);
                }
            }

            // Loops through the vector and turns it to a string
            for (unsigned char c : newPasswordC) {
                passwordString += static_cast<char>(c);
            }

            // Checks the strings equality and safepasswords
            //cout << "|PASS " << passwordString << "|RES " << result->password << "|SUB " << passwordString.substr(0, 1) << "|" << endl;
            
            if (passwordString != result->password) {
                // If it failed try again with safePassword

                // Init
                int safePos = 0;
                int lengthSafe = 0;
                int secLengthSafe = 0;
                string safePassword;

                // Make uniq if user hasn't put it themselves
                if (result->safe == false) {
                    deviceId(result);
                }
            
                // Length of uniq
                lengthSafe = result->uniq.length();
                // passwordstring - uniq length
                secLengthSafe = passwordString.length() - lengthSafe;
                try {
                    // String length = substring = oikea salasana
                    safePassword = passwordString.substr(secLengthSafe);
                }
                catch (const std::exception& error){
                    //std::cerr << "Error reading file. " << error.what() << std::endl;
                    std::cerr << "Error reading file. Password is incorrect or the computer is not the same this file was encrypted on." << std::endl;
                    exitfailure();
                }
                //cout << "1: " << lengthSafe << " = " << secLengthSafe << endl;
                //cout << "2: " << result->password << " = " << passwordString.substr(0, secLengthSafe) << endl;
                //cout << "3: " << safePassword << " = " << result->uniq << endl;
                // Checks the strings equality and safepasswords
                if (!(safePassword == result->uniq && result->password == passwordString.substr(0, secLengthSafe))) {
                    // Exit the program on failure
					cout << "Password is incorrect or the computer is not the same this file was encrypted on." << endl;
					exitfailure();
                }
            } // PASSWORDSTRING
            
            // EXTENSION
            // Decrypt the extension
            std::vector<unsigned char> newExtensionC;
            std::vector<unsigned char> newExtensionCVector;
            string newExtensionS;

            // Get extension
            extractedSubstring = line.substr(line.find(toFind) + toFind.length(), line.find(memF_2) - (line.find(toFind) + toFind.length()));
            //cout << extractedSubstring << endl;
            // Turn ext to vector
            for (char c : extractedSubstring) {
                // Push value to vector as unsigned char
                int value = static_cast<int>(static_cast<unsigned char>(c));
                newExtensionCVector.push_back(c);
            }


            // If no file extension skip this
            //cout << newExtensionCVector.size() << " a" << endl;
            if (newExtensionCVector.size() != 0) {
                newExtensionC = deCrypt(newExtensionCVector, result, 1);
                // Check for \r\n
                for (unsigned char& c : newExtensionC) {
                    if (static_cast<int>(c) == 14 || static_cast<int>(c) == 11) { // If char is 14 or 11 = \r +1 && \n + 1
                        // remove 1
                        c = static_cast<unsigned char>(static_cast<int>(c) - 1);
                    }
                }
            }


            // Change extension to decrypt
            for (char c : newExtensionC) {
                newExtensionS += c;
            }

            //cout << "|" << newExtensionS << "|" << endl;
            // Check if it doesn't have extension.
            if (newExtensionS != "") {
                // Get part excluding .ext part
                newPathToFile = fullPath.substr(0, pos);

                // Add old file extension
                prev = "." + newExtensionS;
                newPathToFile += prev;
            }
            else {
                // No file extension, the path is the same but without .atk
                newPathToFile = fullPath.substr(0, pos);
            }

            // Add newpath to result
            result->newPath = newPathToFile;
        }
    }

    // ! 
    // ! Reads filedata
    // ! 
    if (newfile.is_open()){   // Checks if file is open
        string line;

        /*
        Vector that will hold the values
        of each byte in hexadeciaml
        */
        std::vector<unsigned char> hexData;

        char byte;
        
        while (newfile.read(&byte, 1)) {
            // Store the byte in the vector
            hexData.push_back(static_cast<unsigned char>(byte));
        }

        /* MEM
        for (unsigned char c : hexData) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c) << " ";
            std::cout << std::dec << std::setw(2) << std::setfill('0') << static_cast<int>(c) << endl;
        } 
        */

        newfile.close(); // Closes the file




        // ! Checks if file is .atk file
        if (fullPath.substr(pos, fullPath.length()) == ".atk") {
            writeFile(hexData, result, 1, true);
        } 

        // ! If not .atk file
        else {
            // Write the data
            writeFile(hexData, result, 1, false);
        }

    } // End of newfile.open
}
