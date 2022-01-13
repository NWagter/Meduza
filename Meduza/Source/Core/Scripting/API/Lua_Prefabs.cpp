#include "MePCH.h"
#include "Core/Scripting/API/Lua_Prefabs.h"

#include "MeduzaIncluder.h"
#include "Core/Scripting/API/Lua_APIHelper.h"


void Me::Scripting::Lua_API::Lua_Prefabs::RegisterPrefabsFunctions(lua_State* a_luaState)
{
    lua_register(a_luaState, "_InstantiatePrefab", lua_InstantiatePrefab);
}

int Me::Scripting::Lua_API::Lua_Prefabs::lua_InstantiatePrefab(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 2) return -1;

    std::string path = lua_tostring(a_luaState, 1);
    Me::Math::Vec3 location = Lua_Helper::GetVector3(a_luaState, 2);

    size_t pos = path.find("Projects"); //find location of word
    path.erase(0,pos); //delete everything prior to location found
    std::replace(path.begin(), path.end(), '\\', '/');

    EntityID newEntity = Serialization::Serializer::GetInstance()->DeserializeEntity(path);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(newEntity);
    auto physics = EntityManager::GetEntityManager()->GetComponent<Physics::PhysicsComponent>(newEntity);
    
    if(trans == nullptr)
    {
        return -1;
    }

    trans->m_translation = location;

    lua_pushnumber(a_luaState, (uint32_t)newEntity);
    return 1;
}
