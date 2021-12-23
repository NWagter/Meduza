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