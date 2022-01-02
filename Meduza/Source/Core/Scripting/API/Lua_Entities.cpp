#include "MePCH.h"
#include "Core/Scripting/API/Lua_Entities.h"

#include "MeduzaIncluder.h"

void Me::Scripting::Lua_API::Lua_Entities::RegisterEntityFunctions(lua_State* a_luaState)
{
    lua_register(a_luaState, "_DestroyEnt", lua_DestroyEnt);
    lua_register(a_luaState, "_GetEntityByName", lua_GetEntityByName); 
}

int Me::Scripting::Lua_API::Lua_Entities::lua_DestroyEnt(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 1) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);

    EntityManager::GetEntityManager()->DestroyEntity(ent);

    lua_pushnumber(a_luaState, 1);
     
    return 1;
}

int Me::Scripting::Lua_API::Lua_Entities::lua_GetEntityByName(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 1) return -1;

    std::string const& name = lua_tostring(a_luaState, 1);

    EntityFilter filter;
    filter.insert(TagComponent::s_componentID);
    
    EntityManager* eManager = EntityManager::GetEntityManager();
    std::vector<EntityID> const& ents = eManager->GetEntities(filter);

    for(auto e : ents)
    {
        TagComponent* t = eManager->GetComponent<TagComponent>(e);

        if(t->m_tag == name)
        {            
            lua_pushnumber(a_luaState, (uint32_t)e);
            return 1;
        }
    }

    lua_pushnumber(a_luaState, 0); 

    return 0;
}