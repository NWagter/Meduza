#include "MePCH.h"
#include "Core/Scripting/API/Lua_Math.h"

#include "MeduzaIncluder.h"

void Me::Scripting::Lua_API::Lua_Math::RegisterMathFunctions(lua_State* a_luaState)
{
    lua_register(a_luaState, "_CreateVector2", lua_CreateVector2);
    lua_register(a_luaState, "_CreateVector3", lua_CreateVector3);
    lua_register(a_luaState, "_GetDistance", lua_GetDistance);
}

int Me::Scripting::Lua_API::Lua_Math::lua_CreateVector2(lua_State* a_luaState)
{

    return 1;
}

int Me::Scripting::Lua_API::Lua_Math::lua_CreateVector3(lua_State* a_luaState)
{
    
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