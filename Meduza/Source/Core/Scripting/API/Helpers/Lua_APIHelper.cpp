#include "MePCH.h"

#include "Core/Scripting/API/Helpers/Lua_APIHelper.h"
#include "Core/Scripting/API/Helpers/Lua_MathHelper.h"

#include "Core/ValueContainer.h"
#include "Core/Scripting/ScriptComponentHelper.h"

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
            Lua_MathHelper::CreateVector3(a_luaState, static_cast<ValueVector3*>(value)->m_value);
        }
        break;
        case ValueType::Entity:
        {
            EntityID entID = static_cast<ValueEntity*>(value)->m_value;
            if (entID == ENTITY_NULL)
            {
                ME_LUA_WARNING("No Entity assigned to : %s \n", value->m_argumentName.c_str());
                lua_pushnil(a_luaState);
                break;
            }

            lua_pushnumber(a_luaState, (uint32_t)entID);
        }
        break;
        case ValueType::Asset:
        {
            std::string const assetPath = static_cast<ValueAsset*>(value)->m_value;

            if(assetPath.empty())
            {
                ME_LUA_WARNING("No Asset assigned to : %s \n", value->m_argumentName.c_str());
                lua_pushnil(a_luaState);
                break;
            }

            lua_pushstring(a_luaState, assetPath.c_str());
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