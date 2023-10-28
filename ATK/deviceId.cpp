#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include "deviceId.h"
#include "argHeader.h"
#pragma comment(lib, "user32.lib")

void deviceId(basicInfo* result) {
    std::string results = "";
    SYSTEM_INFO siSysInfo;
    // Copy the hardware information to the SYSTEM_INFO structure. 

    GetSystemInfo(&siSysInfo);

    results += std::to_string(siSysInfo.dwActiveProcessorMask);
    results += std::to_string(siSysInfo.dwAllocationGranularity);
    results += std::to_string(siSysInfo.dwNumberOfProcessors);
    results += std::to_string(siSysInfo.dwOemId);
    results += std::to_string(siSysInfo.dwPageSize);
    results += std::to_string(siSysInfo.dwProcessorType);
    results += std::to_string(siSysInfo.wProcessorArchitecture);
    results += std::to_string(siSysInfo.wProcessorLevel);
    results += std::to_string(siSysInfo.wProcessorRevision);
    results += std::to_string(siSysInfo.wReserved);

    result->uniq = results;
}

