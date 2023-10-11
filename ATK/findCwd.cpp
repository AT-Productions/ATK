#include <string>
#ifdef __linux__
#include <unistd.h>
#include <limits.h>
#else
#include <direct.h>
#endif

#include <fstream>

using namespace std;

#include "findCwd.h"
#include "exitFailure.h"

string findCwd(string path){
    string fullPath;
    #ifdef __linux__
        char buffer[PATH_MAX];
    #else
        char buffer[_MAX_PATH];
    #endif

    #ifdef __linux__
        // Checks for cwd
        if(getcwd(buffer, sizeof(buffer)) != nullptr){
            /* Build the path */

            // Get filename:
            string fileName = "/" + fullPath.substr(fullPath.find_last_of("/") + 1);

            // Add the buffer (call location) and fileName to create the fullpath
            fullPath = buffer + fileName;
        }
    
    #else
        if (_getcwd(buffer, sizeof(buffer)) != nullptr) {
            /* Build the path */

            // get the filename
            string fileName = "\\" + path.substr(fullPath.find_last_of("\\") + 1);

            // Add the buffer (call location) and fileName to create the fullpath
            fullPath = buffer + fileName;
        } else {
            perror("_getcwd");
            exitfailure();
        }
    #endif
    return fullPath;
}