#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "argHeader.h"
#include "readFile.h"
#include "exitFailure.h"
#include "writeFile.h"
#include "findCwd.h"

//https://www.youtube.com/watch?v=4l5HdmPoynw
extern "C" {
#include "lua535/include/lua.h"
#include "lua535/include/lauxlib.h"
#include "lua535/include/lualib.h"
}

#ifdef _WIN32
#pragma comment(lib, "lua535/lua53.lib")
#endif // _WIN32



/*
https://stackoverflow.com/questions/23461499/decimal-to-unicode-char-in-c
https://stackoverflow.com/questions/49907441/type-in-special-characters-and-save-in-file
#include <locale>
#include <codecvt>
#include <io.h>
#include <fcntl.h>
*/

using namespace std;
/**
 * Reads given file
 * @param filepath path to the given file which will be read by this function
*/
void readFile(string filePath, basicInfo* result){
    std::string cmd = "a=7+11";

    lua_State* L = luaL_newstate();

    int r = luaL_dostring(L, cmd.c_str());

    // Check for errors
    if (r == LUA_OK) {
        lua_getglobal(L, "a");
        if (lua_isnumber(L, -1)) {
            float a_in_cpp = (float)lua_tonumber(L, -1);
            cout << a_in_cpp << endl;
        }
    }
    else {
        std::string errormsg = lua_tostring(L, -1);
        std::cout << errormsg << std::endl;
    }
    lua_close(L);
    exitfailure();

    string fullPath = filePath;

    /* Checks if path contains string: ./ or .\ */
    if(filePath.substr(0, 2) == ".\\" || filePath.substr(0,2) == "./"){
        fullPath = findCwd(filePath);
    }
    /* Checks if given path exists*/
    if( !filesystem::exists(fullPath) ){
        cerr << fullPath << " Is invalid" << endl;
        exitfailure();
    }

    // Add path to result
    result->path = fullPath;

    /**
     * ------------------------------------
     * 
    New file */
    fstream newfile;

    // Holds value of the new pathfile
    string newPathToFile;
   /**
     * Reads file line by line
    */


    newfile.open(filePath, ios::in); // Open file using read operation
    // Make new path for new file
    // /old/path/name.atk
    // Changes .ext to atk

    // Get position of last '.'
    const int pos = fullPath.find_last_of(".");
    // cout << "AAA " << result->path << endl;
    // cout << "BBB " << newPathToFile << endl;
    // !
    // ! Checks if file is not .atk file
    // !
    if (fullPath.substr(pos, fullPath.length()) != ".atk") {
        // Create new substring excluding the .ext part
        newPathToFile = fullPath.substr(0, pos);
        // Add .atk file extension
        newPathToFile = newPathToFile + ".atk";

       // Initialize files header section with @param 0
       writeFile("" ,result, 0, 0, newPathToFile);
    }
    else { // If .atk file
        // GET PREVIOUS FILE EXTENSION FROM THE FILE
        string prev;
        if(newfile.is_open()) {
            string line;
            while (getline(newfile, line)) { // Reads file contents line by line

                // ! No idea why _PASSWORD_ returns the line of _EXTENSION_
                // ! But it does...
                if (line.find("_PASSWORD_")) { // Find _EXTENSION_
                    prev = line.substr(line.find_last_of("_") + 1, line.length());
                    break;
                }
            }
        }
        // HERE AS PLACEHOLDER
        newPathToFile = fullPath.substr(0, pos);
        newPathToFile = newPathToFile + prev;
    }








    if (newfile.is_open()){   // Checks if file is open
        string line;
        string data;
        int i = 0;


        // !
        // ! Checks if file is .atk file
        // !
        if (fullPath.substr(pos, fullPath.length()) == ".atk") {
            // First 3 rows = Headers. after that file content.
            while (getline(newfile, line)) { 
                // Reads file contents line by line
                // Write to the given file current line.

                // STARTS STRAIGHT FROM DATA
                // DUE TO EARLIER READING    

                data += line;

                // Add the current line to data
                // i++;
            }
            newfile.close(); // Closes the file
            writeFile(data, result, 1, true, newPathToFile);

        } else { // If not .atk file
            while(getline(newfile, line)){ 
                // Reads file contents line by line
                // Write to the given file current line.

                // First row = don't make new row
                if (i < 3) {
                    data += line;
                } else {
                    data += line;
                }
                // Add the current line to data
                i++;
            }
            newfile.close(); // Closes the file
            // Write the data
            writeFile(data, result, 1, false, newPathToFile);
        }
        // End files block with ]
        // ! Moved "temporarily" to writeFile.cpp
        // writeFile("]", result, 1, 1, newPathToFile);

    } // End of newfile.open

    // Change back to original
    std::locale::global(std::locale("C"));
}
