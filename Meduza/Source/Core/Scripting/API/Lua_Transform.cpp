#include "MePCH.h"
#include "Core/Scripting/API/Lua_Transform.h"

#include "MeduzaIncluder.h"
#include "Core/Scripting/API/Helpers/Lua_APIHelper.h"
#include "Core/Scripting/API/Helpers/Lua_MathHelper.h"

#include "Physics/Components/PhysicsComponent.h"

void Me::Scripting::Lua_API::Lua_Transform::RegisterTransformFunctions(lua_State* a_luaState)
{
    lua_register(a_luaState, "_Translate", lua_Translate);

    lua_register(a_luaState, "_SetLocation", lua_SetLocation);
    lua_register(a_luaState, "_GetLocation", lua_GetLocation);

    lua_register(a_luaState, "_Move", lua_Move);
    lua_register(a_luaState, "_Rotate", lua_Rotate);
    lua_register(a_luaState, "_LookAt", lua_LookAt);
    lua_register(a_luaState, "_SetRotation", lua_SetRotation);
    lua_register(a_luaState, "_SetScale", lua_SetScale);

    lua_register(a_luaState, "_FlipX", lua_FlipX);
    lua_register(a_luaState, "_FlipY", lua_FlipY);
}

int Me::Scripting::Lua_API::Lua_Transform::lua_Translate(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 2)
    {
        return -1;
    }
    
    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    Math::Vector3 translation = Lua_MathHelper::GetVector3(a_luaState, 2);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    trans->m_translation += translation;

    return 0;
}

int Me::Scripting::Lua_API::Lua_Transform::lua_Rotate(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 2)
    {
        return -1;
    }

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    Math::Vector3 rotation = Lua_MathHelper::GetVector3(a_luaState, 2);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    trans->m_rotation += rotation;

    return 0;
}

int Me::Scripting::Lua_API::Lua_Transform::lua_GetLocation(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 1) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);

    if(trans == nullptr)
        return -1;

    lua_newtable(a_luaState);

    lua_pushstring(a_luaState, "x");
    lua_pushnumber(a_luaState, trans->m_translation.m_x);
    lua_settable(a_luaState, -3);
    
    lua_pushstring(a_luaState, "y");
    lua_pushnumber(a_luaState, trans->m_translation.m_y);
    lua_settable(a_luaState, -3);
    
    lua_pushstring(a_luaState, "z");
    lua_pushnumber(a_luaState, trans->m_translation.m_z);
    lua_settable(a_luaState, -3);

    luaL_getmetatable(a_luaState, "Vector3");
    lua_setmetatable(a_luaState, -2);

    return 1;
}

int Me::Scripting::Lua_API::Lua_Transform::lua_Move(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 2)
    {
        return -1;
    }
          
    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    Me::Math::Vector3 move = Lua_MathHelper::GetVector3(a_luaState, 2);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    Me::Math::Matrix4 transform = Me::Math::Matrix4().Rotation(trans->m_rotation);
    
    Me::Math::Vector3 right = transform.GetRight() * move.m_x;
    Me::Math::Vector3 up = transform.GetUp() * move.m_y;
    Me::Math::Vector3 forward = transform.GetForward() * move.m_z;

    Me::Math::Vector3 movement = forward + right + up;

    Physics::PhysicsComponent* pC = EntityManager::GetEntityManager()->GetComponent<Physics::PhysicsComponent>(ent);
    if (pC != nullptr)
    {
        pC->m_movement += movement;
    }
    else
    {
        trans->m_translation += movement;
    }

    return 0;
}

int Me::Scripting::Lua_API::Lua_Transform::lua_LookAt(lua_State* a_luaState)
{
    if (lua_gettop(a_luaState) != 2)
    {
        return -1;
    }

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    Me::Math::Vector3 target = Lua_MathHelper::GetVector3(a_luaState, 2);

    auto trans = EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    trans->m_rotation = Me::Math::LookAtRotation(target, trans->m_translation);

    return 0;
}

int Me::Scripting::Lua_API::Lua_Transform::lua_SetLocation(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 2)
    {
        return -1;
    }
    
    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    Math::Vector3 translation = Lua_MathHelper::GetVector3(a_luaState, 2);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    trans->m_translation = translation;

    return 0;
}

int Me::Scripting::Lua_API::Lua_Transform::lua_SetRotation(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 2)
    {
        return -1;
    }

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    Math::Vector3 euler = Lua_MathHelper::GetVector3(a_luaState, 2);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    trans->m_rotation = euler;

    return 0;
}

int Me::Scripting::Lua_API::Lua_Transform::lua_SetScale(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 2)
    {
        return -1;
    }

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    Math::Vector3 scale = Lua_MathHelper::GetVector3(a_luaState, 2);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    trans->m_scale = scale;

    return 0;
}

int Me::Scripting::Lua_API::Lua_Transform::lua_FlipX(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 1) return -1;

    if (lua_isnil(a_luaState, 1))
    {
        ME_LUA_ERROR("Entity is Nil!");
        return -1;
    }
    else if (lua_tonumber(a_luaState, 1) <= 0)
    {
        ME_LUA_ERROR("Entity is Invalid! \n");
        return -1;
    }

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    auto scale = trans->m_scale;
    scale.m_x = -scale.m_x;
    trans->m_scale = scale;

    return 0;
}

int Me::Scripting::Lua_API::Lua_Transform::lua_FlipY(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 1) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    auto scale = trans->m_scale;
    scale.m_y = -scale.m_y;
    trans->m_scale = scale;

    return 0;
}