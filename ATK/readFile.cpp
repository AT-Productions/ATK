#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "help.h"
#include "argHeader.h"
#include "readFile.h"
#include "exitFailure.h"
#include "writeFile.h"
#include "findCwd.h"
#include "exitFailure.h"
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
    if (fs::is_directory(fullPath, ec) && (result->type.substr(0, 1) == "f" || result->type.substr(0, 1) == "F")) {
        // Process a directory.
        cout << fullPath << " is a directory. " << shortHelp() << endl;
        exitfailure();
    }
    if (ec) {
        std::cerr << "Error in is_directory: " << ec.message();
    }
    if (fs::is_regular_file(fullPath, ec) && (result->type.substr(0, 1) == "d" || result->type.substr(0, 1) == "D")) {
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
    fstream newfile;

    // Holds value of the new pathfile
    string newPathToFile;

   /**
     * Reads file line by line
    */
    newfile.open(filePath, ios::in | ios::binary); // Open file using read operation

    // Make new path for new file
    // /old/path/name.atk
    // Changes .ext to atk

    // Get position of last '.'
    const int pos = fullPath.find_last_of(".");
    // !
    // ! Checks if file is not .atk file
    // !
    if (fullPath.substr(pos, fullPath.length()) != ".atk") {
        // Create new substring excluding the .ext part
        newPathToFile = fullPath.substr(0, pos);

        // Add .atk file extension
        newPathToFile = newPathToFile + ".atk";

        // Add newpath to result
        result->newPath = newPathToFile;

       // Initialize files header section with @param 0
       writeFile("" ,result, 0, 0);
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
            string toFind = "c?^ | ^?c";
            int separator = line.find(toFind);

            // PASSWORD
            // Reads and decrypts password
            // If they aren't equal, throw error on console

            // Initialize variables
            string passwordString;
            std::vector<char16_t> newPasswordC;

            // Contains vector holding the characters
            newPasswordC = deCrypt(line.substr(0, separator), result);

            // Loops through the vector and turns it to a string
            for (char16_t c : newPasswordC) {
                passwordString += static_cast<char>(c);
            }

            // Checks the strings equality
            if (passwordString != result->password) {
                // Exit the program on failure
                cout << "Password is incorrect, try again." << endl;
                exitfailure();
            }

            // EXTENSION
            // Decrypt the extension
            std::vector<char16_t> newExtensionC;
            string newExtensionS;

            newExtensionC = deCrypt(line.substr(separator + toFind.length(), line.length()), result);
            
            // Change extension to decrypt
            for (char c : newExtensionC) {
                newExtensionS += c;
            }
            prev = "." + newExtensionS;

            // HERE AS PLACEHOLDER
            newPathToFile = fullPath.substr(0, pos);
            newPathToFile = newPathToFile + prev;

            // Add newpath to result
            result->newPath = newPathToFile;
        }
    }

    if (newfile.is_open()){   // Checks if file is open
        string line;
        string data;
        while (getline(newfile, line)) { 
            // Reads file contents line by line
            // Write to the given file current line.

            // Add the current line to data
            data += line + "\n";
        }

        // Remove last letter \n
        // Otherwise it will add an extra null character
        data.pop_back();

        newfile.close(); // Closes the file

        // ! Checks if file is .atk file
        if (fullPath.substr(pos, fullPath.length()) == ".atk") {
            writeFile(data, result, 1, true);
        } 

        // ! If not .atk file
        else {
            // Write the data
            writeFile(data, result, 1, false);
        }

    } // End of newfile.open
}
