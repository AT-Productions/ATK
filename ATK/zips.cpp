#include <iostream>
#include <string>
#include <Windows.h>
#include "exitFailure.h"
#include "zips.h"

using namespace std;
void zip(const char* output, const char* input) {
    //cout << "aa " << output << " " << input << endl;
    // PowerShell script to run
    // Build the PowerShell command to compress the input folder
    std::string powerShellCommand = "powershell -ExecutionPolicy Bypass -Command \"Compress-Archive -Path \'" + std::string(input) + "\' -DestinationPath \'" + std::string(output) + "\'\"";
    //std::string powerShellCommand = "powershell -ExecutionPolicy Bypass -Command \"Compress-Archive -Path 'C:\\Users\\janne\\Desktop\\testi' -DestinationPath 'C:\\Users\\janne\\Desktop\\testi.zip'\"";
    //cout << powerShellCommand << endl;
    // Launch a PowerShell process
    int result = system(powerShellCommand.c_str());

    if (result == 0) {
        //std::cout << "PowerShell script executed successfully." << std::endl;
    }
    else {
        std::cerr << "Error encrypting directory" << std::endl;
        exitfailure();
    }
}

void unzip(const char* input, const char* destination) {
    // Unzips files.
    // Build the PowerShell command to extract the archive
    std::string powerShellCommand = "powershell -ExecutionPolicy Bypass -Command \"Expand-Archive -Path \'" + std::string(input) + "\' -DestinationPath \'" + std::string(destination) + "\'\"";
    //cout << powerShellCommand << endl;
    // Launch a PowerShell process
    int result = system(powerShellCommand.c_str());

    if (result == 0) {
        //std::cout << "PowerShell script executed successfully." << std::endl;
    }
    else {
        std::cerr << "Error encrypting directory" << std::endl;
    }
}