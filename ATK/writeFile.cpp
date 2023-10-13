#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <vector>

#include "argHeader.h"
#include "writeFile.h"
#include "cryption.h"
#include "exitFailure.h"

//https://www.youtube.com/watch?v=4l5HdmPoynw
#include "checkLua.h"
#include "lua535/include/lua.hpp"

#ifdef _WIN32
#pragma comment(lib, "lua535/lua53.lib")
#endif // _WIN32

using namespace std;

void writeFile(string content = "", basicInfo* result = nullptr, int action = 1, bool decrypt = false, string newPathToFile = "") {
    int currentrow = 0;

    // Open in append mode

    // Do initialization with action0
    if(action == 0){

        // Delete old file
        remove(newPathToFile.c_str());


        // Create new file or modify it
        ofstream newFile(newPathToFile, ios::app);
        /**
         * ---------------------------------------------
         * Starts writing to new file
         * 
         * cryptFunc("string");
        */
        
        newFile /* << currentrow++ */ << "_PASSWORD_" << passwordHash(result) << endl;

        // Adds the original file extension. Finds position of the last '.' and takes a substring from it to the end of the string
        newFile /* << currentrow++ */ <<  "_EXTENSION_" << result->path.substr(result->path.find_last_of("."), result->path.length()) << endl;
        // newFile << "BLOCK0" << result->path.substr(pos, result->path.length()) << currentrow++ << " ENDROW " << endl; ;
    }

    // Make BLOCKS with action1
    if(action == 1){
        ofstream newFile(newPathToFile, std::ios::app | std::ios::binary);
        // ofstream newFile(newPathToFile, ios::app);
        if (newFile.fail()) {
            cerr << "Error opening the file for writing." << endl;
            exitfailure();
        }


        // currentrow = 7 + blockInt;
        std::vector<char32_t> results;
        std::vector<wchar_t> newResults;
        std::string writeStr;
        std::vector<uint16_t> utf16;

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


        // Print the contents of the 'result' vector
        // Using lua

        // Initialize new lua machine
        lua_State* L = luaL_newstate();

        // Opens basic libraries for lua to use
        luaL_openlibs(L);


        int r = luaL_dofile(L, "source/writeFile.lua");
        // Check for errors
        if (checkLua(L, r)) {

            // Gets function
            lua_getglobal(L, "WriteFile");

            // Error check
            if (lua_isfunction(L, -1)) {
                // Create a Lua table to hold the vector elements
                lua_newtable(L);
                // Push the vector elements onto the Lua stack
                int integer = 0;
                for (char32_t c : results) {
                    lua_pushnumber(L, c);
                    wcout << wchar_t(c) << endl;
                    // Set the table entry (Lua is 1-based)
                    lua_rawseti(L, -2, static_cast<lua_Integer>(integer) + 1);
                    integer++;
                }


                lua_pushstring(L, newPathToFile.c_str());

                if (checkLua(L, lua_pcall(L, 2, 1, 0))) {

                     //cout << "GOT: " << (bool)lua_tonumber(L, -1) << endl;
                }
            }

        }
        lua_close(L);



        for (char32_t c : results) {
            if (c <= 0xFFFF) {
                // If the character is within the UTF-16 range
                utf16.push_back(static_cast<uint16_t>(c));
                //wcout << static_cast<uint16_t>(c) << endl;
            }
            else {
                // HANDLE ERRORS
                // COMING SOON
            }
        }

        //// Write the UTF-16 data to the file
        //newFile.write(reinterpret_cast<char*>(utf16.data()), utf16.size() * sizeof(uint16_t));

        //// Close the file
        newFile.close();


        //// Delete the previous file
        if (remove(result->path.c_str()) == 0){
        }
    }
}