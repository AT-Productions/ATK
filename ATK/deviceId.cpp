#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include "deviceId.h"
#include "argHeader.h"
#include "exitFailure.h"
#pragma comment(lib, "user32.lib")


#include <WINSOCK.H>
#pragma comment(lib, "ws2_32.lib")

void deviceId(basicInfo* result) {
    std::string results = "";


    SYSTEM_INFO siSysInfo;
    // Copy the hardware information to the SYSTEM_INFO structure. 

    GetSystemInfo(&siSysInfo);

    results += std::to_string(siSysInfo.dwActiveProcessorMask);
    results += std::to_string(siSysInfo.dwAllocationGranularity);
    results += std::to_string(siSysInfo.dwNumberOfProcessors);
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
        for (char c : hostname) {
            results += c;
            if (i >= 15) { // Maximum amount the comp. name can be
                break;
            }
            i++;
        }
    }
    else {
        std::cout << "Error making unique key with the safe argument." << std::endl;
        exitfailure();
    }

    WSACleanup();
    results += std::to_string(siSysInfo.dwOemId);
    results += std::to_string(siSysInfo.dwPageSize);
    results += std::to_string(siSysInfo.dwProcessorType);
    results += std::to_string(siSysInfo.wProcessorArchitecture);
    results += std::to_string(siSysInfo.wProcessorLevel);
    results += std::to_string(siSysInfo.wProcessorRevision);
    results += std::to_string(siSysInfo.wReserved);

    result->uniq = results;
}

