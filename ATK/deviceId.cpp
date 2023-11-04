#include <windows.h>
#include <string>
#include <iostream>
#include <vector>

#pragma comment(lib, "user32.lib")
#include <Lmcons.h>

#include <WINSOCK.H>
#pragma comment(lib, "ws2_32.lib")

#include "deviceId.h"
#include "argHeader.h"
#include "exitFailure.h"

std::string getUser();
std::string getComputerNameF();

void deviceId(basicInfo* result) {
    std::string results = "";


    // Copy the hardware information to the SYSTEM_INFO structure. 
    SYSTEM_INFO siSysInfo;

    GetSystemInfo(&siSysInfo);

    results += std::to_string(siSysInfo.dwActiveProcessorMask);
    results += std::to_string(siSysInfo.dwAllocationGranularity);
    results += std::to_string(siSysInfo.dwNumberOfProcessors);
    results += getComputerNameF();
    results += std::to_string(siSysInfo.dwOemId);
    results += std::to_string(siSysInfo.dwPageSize);
    results += std::to_string(siSysInfo.dwProcessorType);
    results += std::to_string(siSysInfo.wProcessorArchitecture);
    results += std::to_string(siSysInfo.wProcessorLevel);
    results += getUser();
    results += std::to_string(siSysInfo.wProcessorRevision);
    results += std::to_string(siSysInfo.wReserved);

    result->uniq = results;
}

// @Returns the current username
std::string getUser() {
    TCHAR name[UNLEN + 1];
    DWORD size = UNLEN + 1;

    if (GetUserName((TCHAR*)name, &size)) {
        // WSTRIN TO STRING
        std::wstring wide = name;
        std::string strname(wide.begin(), wide.end());

        std::wstring ws(strname.begin(), strname.end()); // converting strname to ws in its range

        // Error check for possible dataloss
        if (ws != name) {
            std::cerr << "Error making unique key with the safe argument. Possible data loss." << std::endl;
            exitfailure();
        }
        else {
            return strname;
        }
    }
    else {
        std::cerr << "Error making unique key with the safe argument." << std::endl;
        exitfailure();
    }
}

// @Returns the current computer name (DESKTOP-1234567)
std::string getComputerNameF() {
    // Initialize winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        // Handle initialization error
        std::cout << "Error making unique key with safe argument." << std::endl;
        exitfailure();
    }

    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        int i = 0;
        std::string results;
        for (char c : hostname) {
            results += c;
            if (i >= 15) { // Maximum amount the comp. name can be
                break;
            }
            i++;
        }
        WSACleanup();
        return results;
    }
    else {
        std::cerr << "Error making unique key with the safe argument." << std::endl;
        WSACleanup();
        exitfailure();
    }

}