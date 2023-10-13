#ifndef CHECKLUA_H
#define CHECKLUA_H

#include "lua535/include/lua.hpp"

#ifdef _WIN32
#pragma comment(lib, "lua535/lua53.lib")
#endif // _WIN32
/*
 * Returns false if lua spotted error
 *
 * @param *L lua_State
 * @param r Result
 */
bool checkLua(lua_State* L, int r);

#endif // !CHECKLUA_H
