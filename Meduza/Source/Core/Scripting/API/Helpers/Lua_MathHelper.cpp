#include "MePCH.h"

#include "Core/Scripting/API/Helpers/Lua_MathHelper.h"

void Me::Scripting::Lua_API::Lua_MathHelper::CreateVector3(lua_State* a_luaState, Math::Vec3 a_vec)
{
    lua_newtable(a_luaState);

    lua_pushstring(a_luaState, "x");
    lua_pushnumber(a_luaState, a_vec.m_x);
    lua_settable(a_luaState, -3);

    lua_pushstring(a_luaState, "y");
    lua_pushnumber(a_luaState, a_vec.m_y);
    lua_settable(a_luaState, -3);

    lua_pushstring(a_luaState, "z");
    lua_pushnumber(a_luaState, a_vec.m_z);
    lua_settable(a_luaState, -3);

    luaL_getmetatable(a_luaState, "Vector3");
    lua_setmetatable(a_luaState, -2);
}

Me::Math::Vec3 Me::Scripting::Lua_API::Lua_MathHelper::GetVector3(lua_State* a_luaState, int a_id)
{
    Math::Vec3 value;

    if (lua_istable(a_luaState, a_id))
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

void Me::Scripting::Lua_API::Lua_MathHelper::CreateColour(lua_State* a_luaState, Colour a_vec)
{
    lua_newtable(a_luaState);

    lua_pushstring(a_luaState, "r");
    lua_pushnumber(a_luaState, a_vec.m_colour[0]);
    lua_settable(a_luaState, -4);

    lua_pushstring(a_luaState, "g");
    lua_pushnumber(a_luaState, a_vec.m_colour[1]);
    lua_settable(a_luaState, -4);

    lua_pushstring(a_luaState, "b");
    lua_pushnumber(a_luaState, a_vec.m_colour[2]);
    lua_settable(a_luaState, -4);

    lua_pushstring(a_luaState, "a");
    lua_pushnumber(a_luaState, a_vec.m_colour[3]);
    lua_settable(a_luaState, -4);

    luaL_getmetatable(a_luaState, "Colour");
    lua_setmetatable(a_luaState, -2);
}

Me::Colour Me::Scripting::Lua_API::Lua_MathHelper::GetColour(lua_State* a_luaState, int a_id)
{
    Colour colour;

    if (lua_istable(a_luaState, a_id))
    {
        lua_pushstring(a_luaState, "r");
        lua_gettable(a_luaState, a_id);
        colour.m_colour[0] = lua_tonumber(a_luaState, -1);

        lua_pushstring(a_luaState, "g");
        lua_gettable(a_luaState, a_id);
        colour.m_colour[1] = lua_tonumber(a_luaState, -1);

        lua_pushstring(a_luaState, "b");
        lua_gettable(a_luaState, a_id);
        colour.m_colour[2] = lua_tonumber(a_luaState, -1);

        lua_pushstring(a_luaState, "a");
        lua_gettable(a_luaState, a_id);
        colour.m_colour[3] = lua_tonumber(a_luaState, -1);
    }

    return colour;
}