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

void Me::Scripting::LuaScripting::ExecuteScript(std::string a_string)
{
    lua_State * L = luaL_newstate();
    luaL_openlibs(L);

    int state = luaL_dofile(L, a_string.c_str());
    lua_getglobal(L, "Execute");
    
    if(lua_isfunction(L, -1) )
    {
        lua_pcall(L,0,0,0);
    }

    lua_close(L);
}

