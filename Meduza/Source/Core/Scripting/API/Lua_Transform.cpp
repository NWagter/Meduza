#include "MePCH.h"
#include "Core/Scripting/API/Lua_Transform.h"

#include "MeduzaIncluder.h"
#include "Core/Scripting/API/Lua_APIHelper.h"

#include "Physics/Components/PhysicsComponent.h"

void Me::Scripting::Lua_API::Lua_Transform::RegisterTransformFunctions(lua_State* a_luaState)
{
    lua_register(a_luaState, "_Translate", lua_Translate);

    lua_register(a_luaState, "_SetLocation", lua_SetLocation);
    lua_register(a_luaState, "_GetLocation", lua_GetLocation);

    lua_register(a_luaState, "_Move", lua_Move);
    lua_register(a_luaState, "_Rotate", lua_Rotate);
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
    Math::Vec3 translation = Lua_Helper::GetVector3(a_luaState, 2);

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
    Math::Vec3 rotation = Lua_Helper::GetVector3(a_luaState, 2);

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
    Me::Math::Vec3 move = Lua_Helper::GetVector3(a_luaState, 2);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    Me::Math::Mat4 transform = Me::Math::Mat4().Rotation(trans->m_rotation);
    
    Me::Math::Vec3 right = transform.GetRight() * move.m_x;
    Me::Math::Vec3 up = transform.GetUp() * move.m_y;
    Me::Math::Vec3 forward = transform.GetForward() * move.m_z;

    Me::Math::Vec3 movement = forward + right + up;

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

int Me::Scripting::Lua_API::Lua_Transform::lua_SetLocation(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 2)
    {
        return -1;
    }
    
    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    Math::Vec3 translation = Lua_Helper::GetVector3(a_luaState, 2);

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
    Math::Vec3 euler = Lua_Helper::GetVector3(a_luaState, 2);

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
    Math::Vec3 scale = Lua_Helper::GetVector3(a_luaState, 2);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    trans->m_scale = scale;

    return 0;
}

int Me::Scripting::Lua_API::Lua_Transform::lua_FlipX(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 1) return -1;

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