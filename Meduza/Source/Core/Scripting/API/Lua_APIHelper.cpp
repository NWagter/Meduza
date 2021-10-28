#include "MePCH.h"
#include "Core/Scripting/API/Lua_APIHelper.h"

Me::Math::Vec3 Me::Scripting::Lua_API::Lua_Helper::GetVector(lua_State* a_luaState, int a_id)
{
    Math::Vec3 value;

    if(lua_istable(a_luaState, a_id))
    {
        lua_pushstring(a_luaState, "x");
        lua_gettable(a_luaState, a_id);
        value.m_x = lua_tonumber(a_luaState, -1);

        lua_pushstring(a_luaState, "y");
        lua_gettable(a_luaState, a_id);
        value.m_y = lua_tonumber(a_luaState, -1);

        lua_pushstring(a_luaState, "z");
        lua_gettable(a_luaState, a_id);
        value.m_z = lua_tonumber(a_luaState, -1);
    }
    
    return value;
}