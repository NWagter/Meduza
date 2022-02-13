#include "MePCH.h"
#include "Core/Scripting/API/Lua_APIHelper.h"
#include "Core/Scripting/API/Lua_Math.h"

#include "Core/Scripting/ScriptComponentHelper.h"

Me::Math::Vec3 Me::Scripting::Lua_API::Lua_Helper::GetVector3(lua_State* a_luaState, int a_id)
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

void Me::Scripting::Lua_API::Lua_Helper::CreateInitializationTable(lua_State* a_luaState, std::vector<Value*> a_values)
{
    int amount = a_values.size();

    lua_newtable(a_luaState);

    for (auto value : a_values)
    {
        lua_pushstring(a_luaState, value->m_argumentName.c_str());

        switch (value->m_type)
        {
        case ValueType::Boolean:
        {
            lua_pushboolean(a_luaState, static_cast<ValueBool*>(value)->m_value);
        }
        break;
        case ValueType::Number:
        {
            lua_pushnumber(a_luaState, static_cast<ValueNumber*>(value)->m_value);
        }
        break;
        case ValueType::String:
        {
            lua_pushstring(a_luaState, static_cast<ValueString*>(value)->m_value.c_str());
        }
        break;
        case ValueType::Vector3:
        {
            Lua_Math::CreateVector3(a_luaState, static_cast<ValueVector3*>(value)->m_value);
        }
        break;
        }
        lua_settable(a_luaState, -3);
    }

    luaL_getmetatable(a_luaState, "InitTable");
    lua_setmetatable(a_luaState, -2);
}


void Me::Scripting::Lua_API::Lua_Helper::StackDump(lua_State* a_luaState) {
    int i;
    int top = lua_gettop(a_luaState);
    for (i = 1; i <= top; i++) {  /* repeat for each level */
        int t = lua_type(a_luaState, i);
        switch (t) {

        case LUA_TSTRING:  /* strings */
            printf("`%s'", lua_tostring(a_luaState, i));
            break;

        case LUA_TBOOLEAN:  /* booleans */
            printf(lua_toboolean(a_luaState, i) ? "true" : "false");
            break;

        case LUA_TNUMBER:  /* numbers */
            printf("%g", lua_tonumber(a_luaState, i));
            break;

        default:  /* other values */
            printf("%s", lua_typename(a_luaState, t));
            break;

        }
        printf("  ");  /* put a separator */
    }
    printf("\n");  /* end the listing */
}