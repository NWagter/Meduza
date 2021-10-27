#include "MePCH.h"
#include "Core/Scripting/API/Lua_Physics.h"

#include "MeduzaIncluder.h"

#include "Physics/Components/ColliderComponent.h"
#include "Physics/Components/PhysicsComponent.h"


void Me::Scripting::Lua_API::Lua_Physics::RegisterPhysicsFunctions(lua_State* a_luaState)
{
    lua_register(a_luaState, "_GetVelocity", lua_GetVelocity);
    lua_register(a_luaState, "_ApplyForce", lua_ApplyForce);

    lua_register(a_luaState, "_OnTriggerEntityName", lua_OnTriggerEntityName);
    lua_register(a_luaState, "_OnCollisionEntityName", lua_OnCollisionEntityName);
    
}

int Me::Scripting::Lua_API::Lua_Physics::lua_GetVelocity(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 1) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);

    auto physicsComp =  EntityManager::GetEntityManager()->GetComponent<Physics::PhysicsComponent>(ent);

    lua_newtable(a_luaState);

    lua_pushstring(a_luaState, "x");
    lua_pushnumber(a_luaState, physicsComp->m_velocity.m_x);
    lua_settable(a_luaState, -3);
    
    lua_pushstring(a_luaState, "y");
    lua_pushnumber(a_luaState, physicsComp->m_velocity.m_y);
    lua_settable(a_luaState, -3);
    
    lua_pushstring(a_luaState, "z");
    lua_pushnumber(a_luaState, physicsComp->m_velocity.m_z);
    lua_settable(a_luaState, -3);

    luaL_getmetatable(a_luaState, "VectorMetaTable");
    lua_setmetatable(a_luaState, -2);

    return 1;
}

int Me::Scripting::Lua_API::Lua_Physics::lua_ApplyForce(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 4) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    float x = lua_tonumber(a_luaState, 2);
    float y = lua_tonumber(a_luaState, 3);
    float z = lua_tonumber(a_luaState, 4);

    auto physicsComp =  EntityManager::GetEntityManager()->GetComponent<Physics::PhysicsComponent>(ent);
    physicsComp->m_velocity += Me::Math::Vec3(x,y,z);

    return 1;
}

int Me::Scripting::Lua_API::Lua_Physics::lua_OnTriggerEntityName(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 2) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    std::string name = lua_tostring(a_luaState, 2);

    EntityFilter filter;
    filter.insert(TagComponent::s_componentID);
    filter.insert(Physics::ColliderTagComponent::s_componentID);
    filter.insert(Physics::PhysicsComponent::s_componentID);

    EntityManager* eManager = EntityManager::GetEntityManager();
    std::vector<EntityID> ents = eManager->GetEntities(filter);

    for(auto e : ents)
    {
        TagComponent* t = eManager->GetComponent<TagComponent>(e);

        if(t->m_tag == name || name.empty())
        {            
            Physics::PhysicsComponent* c = eManager->GetComponent<Physics::PhysicsComponent>(ent);

            for(auto data : c->m_triggered)
            {
                if(data.m_entity == e)
                {
                    lua_pushnumber(a_luaState, (int)e); 
                    return 1;
                }
            }
        }
    }

    lua_pushnumber(a_luaState, -1); 

    return -1;
}

int Me::Scripting::Lua_API::Lua_Physics::lua_OnCollisionEntityName(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 2) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    std::string name = lua_tostring(a_luaState, 2);

    EntityFilter filter;
    filter.insert(TagComponent::s_componentID);
    filter.insert(Physics::ColliderTagComponent::s_componentID);
    filter.insert(Physics::PhysicsComponent::s_componentID);

    EntityManager* eManager = EntityManager::GetEntityManager();
    std::vector<EntityID> ents = eManager->GetEntities(filter);

    for(auto e : ents)
    {
        TagComponent* t = eManager->GetComponent<TagComponent>(e);

        if(t->m_tag == name)
        {            
            Physics::PhysicsComponent* c = eManager->GetComponent<Physics::PhysicsComponent>(e);

            for(auto data : c->m_collided)
            {
                if(data.m_entity == ent)
                {
                    lua_pushnumber(a_luaState, (int)e); 
                    return 1;
                }
            }
        }
    }

    lua_pushnumber(a_luaState, -1); 

    return -1;
}