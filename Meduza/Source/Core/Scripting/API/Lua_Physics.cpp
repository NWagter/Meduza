#include "MePCH.h"
#include "Core/Scripting/API/Lua_Physics.h"

#include "MeduzaIncluder.h"
#include "Core/Scripting/API/Lua_APIHelper.h"

#include "Physics/Components/ColliderComponent.h"
#include "Physics/Components/PhysicsComponent.h"


void Me::Scripting::Lua_API::Lua_Physics::RegisterPhysicsFunctions(lua_State* a_luaState)
{
    lua_register(a_luaState, "_GetVelocity", lua_GetVelocity);
    lua_register(a_luaState, "_ApplyForce", lua_ApplyForce);

    lua_register(a_luaState, "_OnTrigger", lua_OnTrigger);
    lua_register(a_luaState, "_OnCollision", lua_OnCollision);   
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
    if(lua_gettop(a_luaState) != 2) 
    { 
        return -1;
    }    

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    Me::Math::Vec3 force = Lua_Helper::GetVector(a_luaState, 2);

    auto physicsComp =  EntityManager::GetEntityManager()->GetComponent<Physics::PhysicsComponent>(ent);
    physicsComp->m_velocity += force;    

    return 1;
}

int Me::Scripting::Lua_API::Lua_Physics::lua_OnTrigger(lua_State* a_luaState)
{
    if (lua_gettop(a_luaState) != 1) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);

    EntityManager* eManager = EntityManager::GetEntityManager();

    Physics::PhysicsComponent* c = eManager->GetComponent<Physics::PhysicsComponent>(ent);

    lua_newtable(a_luaState);
    int it = 0;

    for (auto& data : c->m_triggered)
    {
        Physics::TriggerResult result;
        result.m_hit = true;
        result.m_data = data;
        result.m_name = eManager->GetComponent<TagComponent>(data.m_entity)->m_tag;

        TriggerResult(a_luaState, result);
        lua_rawseti(a_luaState, -2, it);
    }

    return 1;
}

int Me::Scripting::Lua_API::Lua_Physics::lua_OnCollision(lua_State* a_luaState)
{
    if (lua_gettop(a_luaState) != 1) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);

    EntityManager* eManager = EntityManager::GetEntityManager();

    Physics::PhysicsComponent* c = eManager->GetComponent<Physics::PhysicsComponent>(ent);

    lua_newtable(a_luaState);
    int it = 0;
    for (auto& data : c->m_collided)
    {
        Physics::CollisionResult result;
        result.m_hit = true;
        result.m_data = data;
        result.m_name = eManager->GetComponent<TagComponent>(data.m_entity)->m_tag; 

        CollisionResult(a_luaState, result);
        lua_rawseti(a_luaState, -2, it);

        it++;
    }

    return 1;
}

void Me::Scripting::Lua_API::Lua_Physics::TriggerResult(lua_State* a_luaState, Physics::TriggerResult& a_result)
{
    lua_newtable(a_luaState);

    lua_pushstring(a_luaState, "hasHit");
    lua_pushboolean(a_luaState, a_result.m_hit);
    lua_settable(a_luaState, -3);

    lua_pushstring(a_luaState, "entity");
    lua_pushnumber(a_luaState, (int)a_result.m_data.m_entity);
    lua_settable(a_luaState, -3);

    lua_pushstring(a_luaState, "name");
    lua_pushstring(a_luaState, a_result.m_name.c_str());
    lua_settable(a_luaState, -3);

    luaL_getmetatable(a_luaState, "TriggerResult");
    lua_setmetatable(a_luaState, -3);
}

void Me::Scripting::Lua_API::Lua_Physics::CollisionResult(lua_State* a_luaState, Physics::CollisionResult a_result)
{
    lua_newtable(a_luaState);

    lua_pushstring(a_luaState, "hasHit");
    lua_pushboolean(a_luaState, a_result.m_hit);
    lua_settable(a_luaState, -3);

    lua_pushstring(a_luaState, "entity");
    lua_pushnumber(a_luaState, (int)a_result.m_data.m_entity);
    lua_settable(a_luaState, -3);

    lua_pushstring(a_luaState, "name");
    lua_pushstring(a_luaState, a_result.m_name.c_str());
    lua_settable(a_luaState, -3);

    luaL_getmetatable(a_luaState, "CollisionResult");
    lua_setmetatable(a_luaState, -3);
}