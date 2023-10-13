#include <string>
#include <iostream>

#include "checkLua.h"
#include "lua535/include/lua.hpp"

#ifdef _WIN32
#pragma comment(lib, "lua535/lua53.lib")
#endif // _WIN32


bool checkLua(lua_State* L, int r) {
	if (r != LUA_OK) {
		std::string errormsg = lua_tostring(L, -1);
		std::cout << errormsg << std::endl;
		return false;
	}
	return true;
}