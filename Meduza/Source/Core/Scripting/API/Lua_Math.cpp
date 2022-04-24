#include "MePCH.h"
#include "Core/Scripting/API/Lua_Math.h"

#include "MeduzaIncluder.h"
#include "Core/Scripting/API/Helpers/Lua_APIHelper.h"
#include "Core/Scripting/API/Helpers/Lua_MathHelper.h"

void Me::Scripting::Lua_API::Lua_Math::RegisterMathFunctions(lua_State* a_luaState)
{
    lua_register(a_luaState, "_CreateVector3", lua_CreateVector3);
    lua_register(a_luaState, "_GetDistance", lua_GetDistance);

    luaL_newmetatable(a_luaState, "Vector3");
    lua_pushstring(a_luaState, "__sub");
    lua_pushcfunction(a_luaState, Sub_Vec3);
    lua_settable(a_luaState, -3);

    luaL_newmetatable(a_luaState, "Vector3");
    lua_pushstring(a_luaState, "__add");
    lua_pushcfunction(a_luaState, Add_Vec3);
    lua_settable(a_luaState, -3);

    luaL_newmetatable(a_luaState, "Vector3");
    lua_pushstring(a_luaState, "__mul");
    lua_pushcfunction(a_luaState, Mul_Vec3);
    lua_settable(a_luaState, -3);
}

int Me::Scripting::Lua_API::Lua_Math::lua_CreateVector3(lua_State* a_luaState)
{
    Me::Math::Vec3 vec3 = Math::Vec3(0);

    if (lua_gettop(a_luaState) == 3)
    {
        vec3.m_x = lua_tonumber(a_luaState, 1);
        vec3.m_y = lua_tonumber(a_luaState, 2);
        vec3.m_z = lua_tonumber(a_luaState, 3);
    }

    Lua_MathHelper::CreateVector3(a_luaState, vec3);

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

int Me::Scripting::Lua_API::Lua_Math::Add_Vec3(lua_State* a_luaState)
{
    if (lua_gettop(a_luaState) != 2)
    {
        return -1;
    }

    Math::Vec3 lhs = Lua_MathHelper::GetVector3(a_luaState, 1);
    Math::Vec3 rhs = Lua_MathHelper::GetVector3(a_luaState, 2);

    Math::Vec3 result = lhs + rhs;

    Lua_MathHelper::CreateVector3(a_luaState, result);

    return 1;
}

int Me::Scripting::Lua_API::Lua_Math::Sub_Vec3(lua_State* a_luaState)
{
    if (lua_gettop(a_luaState) != 2)
    {
        return -1;
    }

    Math::Vec3 lhs = Lua_MathHelper::GetVector3(a_luaState, 1);
    Math::Vec3 rhs = Lua_MathHelper::GetVector3(a_luaState, 2);

    Math::Vec3 result = lhs - rhs;

    Lua_MathHelper::CreateVector3(a_luaState, result);

    return 1;
}

int Me::Scripting::Lua_API::Lua_Math::Mul_Vec3(lua_State* a_luaState)
{
    if (lua_gettop(a_luaState) != 2)
    {
        return -1;
    }

    Math::Vec3 lhs = Lua_MathHelper::GetVector3(a_luaState, 1);
    float rhs = lua_tonumber(a_luaState, 2);

    Math::Vec3 result = lhs * rhs;

    Lua_MathHelper::CreateVector3(a_luaState, result);

    return 1;
}