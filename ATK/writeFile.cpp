#include <fstream>
#include <string>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip> 
#include <locale>
#include <filesystem>
#include "argHeader.h"
#include "writeFile.h"
#include "cryption.h"
#include "exitFailure.h"
#include "zips.h"

using namespace std;

void action0(basicInfo* result);
void action1(basicInfo* result, bool* decrypt, std::vector<unsigned char>* content);

void writeFile(std::vector<unsigned char> content, basicInfo* result = nullptr, int action = 1, bool decrypt = false) {
    // Do initialization with action0

    // Delete old file
    if (action == 0) {
        if (remove(result->newPath.c_str()) == 0) {}
        /*else {
			cerr << "Error deleting the file." << endl;
			exitfailure();
        }*/
    }


    // Set chinese utf as locale
    std::locale::global(std::locale("en_US.UTF-8"));
    //newFile.imbue(std::locale("zh_CN.UTF-8"));

    if (action == 0) {
        // Do action0. HEADER
        action0(result);
    }

    // Make BLOCKS with action1
    if (action == 1) {
        bool* ptr = &decrypt;
        std::vector<unsigned char>* strptr = &content;
        action1(result, ptr, strptr);

        delete ptr;
        delete strptr;

        ptr = nullptr;
        strptr = nullptr;
    }
}

void action0(basicInfo* result) {
    // Crypted versions of password and file extension
    std::vector<unsigned char> newPasswordC, newExtensionC;
    std::vector<unsigned char> newPasswordCVector, newExtensionCVector;

    // Turn password and extension to unsigned char vectors:

    // Password to unsigned vector
    for (char c : result->password) {
        // Push value to vector as unsigned char
        int value = static_cast<int>(static_cast<unsigned char>(c));
        newPasswordCVector.push_back(value);
    }

    // If keyword -s has been used
    if (result->safe == true) {
        // Add uniq string
        for (char c : result->uniq) {
            int value = static_cast<int>(static_cast<unsigned char>(c));
            newPasswordCVector.push_back(value);
        }
    }

    // Crypt vector
    result->plength = newPasswordCVector.size();
    newPasswordC = crypt(newPasswordCVector, result);

    // Check for \r\n
    for (unsigned char& c : newPasswordC) {
        if (static_cast<int>(c) == 13 || static_cast<int>(c) == 10) { // If char is 13 or 10 \r\n
            // Add 1
            c = static_cast<unsigned char>(static_cast<int>(c) + 1);
        }
    }

    // String versions
    string newPasswordS;
    string newExtensionS;

    // Change password to crypt string
    for (unsigned char c : newPasswordC) {
        newPasswordS += static_cast<char>(c);
    }

    // ! EXTENSION !
    if (result->type != "d" && result->type != "dir") {
        // EXT to unsigned vector
        for (char c : result->path.substr(result->path.find_last_of(".") + 1)) {
            // Push value to vector as unsigned char
            int value = static_cast<int>(static_cast<unsigned char>(c));
            newExtensionCVector.push_back(value);
        }

        int secPos = result->path.find_last_of("\\");

        string newStringMem = result->path.substr(secPos + 1);
        // If it has a . in it
        if (newStringMem.find_last_of(".") != -1) {
            // Use .
            result->elength = newExtensionCVector.size();

            newExtensionC = crypt(
                newExtensionCVector, result
            );

        }
        else {
            // Don't use . add empty

            // ! THIS CODE HERE
            // I
            // I
            // V
            // MAY LEAD TO ISSUES !
            //
            result->elength = newExtensionCVector.size();

            newExtensionC = { 20 };
        }
    }
    else {
        newExtensionCVector = { 'z', 'i', 'p'};
        newExtensionC = crypt(
			newExtensionCVector, result
		);
    }
    // Check for \r\n
    for (unsigned char& c : newExtensionC) {
        if (static_cast<int>(c) == 13 || static_cast<int>(c) == 10) { // If char is 13 or 10 \r\n
            // Add 1
            c = static_cast<unsigned char>(static_cast<int>(c) + 1);
        }
    }

    // Change extension to crypt string
    for (unsigned char c : newExtensionC) {
        newExtensionS += static_cast<char>(c);
    }

    // Writes password and extension. below is seperator
    std::string headerString;
    if (result->type == "d" || result->type == "dir") {
        headerString = "DIRECTORY \n" +
            std::to_string(result->elength) +
            "3hzk233dr198_DATA011kpp253" +
            std::to_string(result->plength) +
            "kl_STM-pfge9132zbag91_META0312" +
            newPasswordS +
            "41adc_c?^ | ^?cd-cgga" +
            newExtensionS;
    }
    else {
        headerString = "FILE \n" +
                std::to_string(result->elength) +
				"3hzk233dr198_DATA011kpp253" +
				std::to_string(result->plength) +
				"kl_STM-pfge9132zbag91_META0312" +
				newPasswordS +
				"41adc_c?^ | ^?cd-cgga" +
				newExtensionS;
    }

    result->header = headerString;
}

void action1(basicInfo* result, bool* decrypt, std::vector<unsigned char>* content) {
    std::vector<unsigned char> results;
    /* DECRYPT THE FILE */
    if (*decrypt == true) {
        // Decrypt the contents and get the result vector
        results = deCrypt(*content, result, 2);
    }

    /*CRYPT THE FILE*/
    else {
        // Crypt the content and get the result vector
        result->dlength = content->size();
        results = crypt(*content, result);
    }
    // Create an empty string to store the result
    std::string resultString;
    if(result->header.empty() == false){
        resultString = result->header + "w01|_DATAMSTRT_##+1ld13" + std::to_string(result->dlength) + "\n";
    }
    // Write the results to the file
    // Create new file or modify it
    ofstream newFile(result->newPath, std::ios::app | std::ios::binary);
    if (newFile.fail()) {
        cerr << "Error opening the file for writing." << endl;
        exitfailure();
    }

    // Write to file
    std::string resultString2(results.begin(), results.end());
    resultString +=  resultString2;
    newFile << resultString;


    // Close the file
    newFile.close();

    // Delete the previous file
    if (result->type != "d" && result->type != "dir") {
        if (remove(result->path.c_str()) == 0) {}
    }
    // Delete the directory
    else {
        // Delete directory at result->path

        // Delete the zip file
        //cout << result->path.substr(0, result->path.find_last_of("zip") - 3) + "\\" << endl;
        //cout << result->path << endl;
        //cout << result->newPath << endl;
        /*
        C:\Users\anton\source\repos\ATK\installation\test\admin\
        C:\Users\anton\source\repos\ATK\installation\test\admin.zip
        C:\Users\anton\source\repos\ATK\installation\test\admin.atk
        
        */
        // If file is .atk
        if (result->type == "d" || result->type == "dir") {
            // UNZIP ZIP
            // REMOVE ZIP
            if (result->path.substr(result->path.find_last_of(".") + 1) == "atk") {
                std::string outputPath = result->newPath.substr(0, result->path.find_last_of("zip") - 3) + "\\";
                unzip(result->newPath.c_str(), outputPath.c_str());

                // Delete atk file
                if (remove(result->path.c_str()) == 0) {}
                // Delete the zip file
                if (remove(result->newPath.c_str()) == 0) {}

            }
            // REMOVE ORIGINAL DIR
            // REMOVE ZIP
            else {
			    //if (remove(result->path.c_str()
			    // Delete the zip file
                if (remove(result->path.c_str()) == 0) {}
                // Delete the directory
                if (std::filesystem::remove_all(result->path.substr(0, result->path.find_last_of("zip") - 3) + "\\") == 0) {}

            }

        }
        //std::filesystem::remove_all( result->path.substr(0, result->path.find_last_of("zip") - 3) + "\\");
    }
    /*else {
		cerr << "Error deleting file." << endl;
		exitfailure();
    }*/
}