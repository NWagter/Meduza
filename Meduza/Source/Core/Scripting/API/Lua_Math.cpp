#include "MePCH.h"
#include "Core/Scripting/API/Lua_Math.h"

#include "MeduzaIncluder.h"
#include "Core/Scripting/API/Lua_APIHelper.h"

void Me::Scripting::Lua_API::Lua_Math::RegisterMathFunctions(lua_State* a_luaState)
{
    lua_register(a_luaState, "_CreateVector3", lua_CreateVector3);
    lua_register(a_luaState, "_GetDistance", lua_GetDistance);
}

int Me::Scripting::Lua_API::Lua_Math::lua_CreateVector3(lua_State* a_luaState)
{
    Me::Math::Vec3 vec3 = Math::Vec3(0);

    if(lua_gettop(a_luaState) == 3)
    {
        vec3.m_x = lua_tonumber(a_luaState, 1);
        vec3.m_y = lua_tonumber(a_luaState, 2);
        vec3.m_z = lua_tonumber(a_luaState, 3);
    }

    lua_newtable(a_luaState);

    lua_pushstring(a_luaState, "x");
    lua_pushnumber(a_luaState, vec3.m_x);
    lua_settable(a_luaState, -3);
    
    lua_pushstring(a_luaState, "y");
    lua_pushnumber(a_luaState, vec3.m_y);
    lua_settable(a_luaState, -3);

    lua_pushstring(a_luaState, "z");
    lua_pushnumber(a_luaState, vec3.m_z);
    lua_settable(a_luaState, -3);

    luaL_getmetatable(a_luaState, "Vector3");
    lua_setmetatable(a_luaState, -2);
    return 1;
}

int Me::Scripting::Lua_API::Lua_Math::lua_GetDistance(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 2) return -1;

    EntityID entA = (EntityID)lua_tonumber(a_luaState, 1);
    EntityID entB = (EntityID)lua_tonumber(a_luaState, 2);

    
    auto transA =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(entA);
    auto transB =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(entB);

    float distance = Math::Distance(transA->m_translation, transB->m_translation);

    
    lua_pushnumber(a_luaState, distance); 

    return 1;
}