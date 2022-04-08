#include "MePCH.h"
#include "Core/Scripting/API/Lua_Debug.h"

#include "MeduzaIncluder.h"

void Me::Scripting::Lua_API::Lua_Debug::RegisterEntityFunctions(lua_State* a_luaState)
{
	lua_register(a_luaState, "_Assert", lua_Assert);
	lua_register(a_luaState, "_LogError", lua_LogError);
	lua_register(a_luaState, "_LogWarning", lua_LogWarning);
	lua_register(a_luaState, "_Log", lua_Log);
}

int Me::Scripting::Lua_API::Lua_Debug::lua_Assert(lua_State* a_luaState)
{
	if (lua_gettop(a_luaState) != 2) return -1;

	bool const assert = lua_toboolean(a_luaState, 1);
	std::string const& msg = lua_tostring(a_luaState, 2);

	ME_LUA_ASSERT_M(assert, msg.c_str());

	return 1;
}

int Me::Scripting::Lua_API::Lua_Debug::lua_LogError(lua_State* a_luaState)
{
	if (lua_gettop(a_luaState) != 1) return -1;

	std::string const& log = lua_tostring(a_luaState, 1);

	ME_LUA_ERROR("%s \n", log.c_str());

	return 1;
}

int Me::Scripting::Lua_API::Lua_Debug::lua_LogWarning(lua_State* a_luaState)
{
	if (lua_gettop(a_luaState) != 1) return -1;

	std::string const& warning = lua_tostring(a_luaState, 1);

	ME_LUA_WARNING("%s \n", warning.c_str());

	return 1;
}

int Me::Scripting::Lua_API::Lua_Debug::lua_Log(lua_State* a_luaState)
{
	if (lua_gettop(a_luaState) != 1) return -1;

	std::string const& log = lua_tostring(a_luaState, 1);

	ME_LUA_LOG("%s \n", log.c_str());

	return 1;
}
