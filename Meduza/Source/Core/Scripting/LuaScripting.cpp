#include "MePCH.h"
#include "Core/Scripting/LuaScripting.h"

#include "Platform/General/FileSystem/FileSystem.h"

Me::Scripting::LuaScripting* Me::Scripting::LuaScripting::ms_instance = nullptr;

Me::Scripting::LuaScripting::LuaScripting()
{
    ms_instance = this;

}

Me::Scripting::LuaScripting::~LuaScripting()
{
    
}

static int MyFunc(lua_State* L)
{
    ME_LOG("Hello World ! \n");
    return 0;
}

void Me::Scripting::LuaScripting::ExecuteScript(std::string a_string, float a_dt)
{
    lua_State * L = luaL_newstate();
    luaL_openlibs(L);
    int state = luaL_dofile(L, a_string.c_str());

    lua_register(L, "_Func", MyFunc);
    lua_getglobal(L, "OnUpdate");
    
    if(lua_isfunction(L, -1) )
    {
        lua_pushnumber(L, a_dt);
        lua_pcall(L,1,0,0);
    }

    lua_close(L);
}

