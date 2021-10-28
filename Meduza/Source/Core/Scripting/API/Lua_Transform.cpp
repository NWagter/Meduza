#include "MePCH.h"
#include "Core/Scripting/API/Lua_Transform.h"

#include "MeduzaIncluder.h"

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
    if(lua_gettop(a_luaState) != 4) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    float x = lua_tonumber(a_luaState, 2);
    float y = lua_tonumber(a_luaState, 3);
    float z = lua_tonumber(a_luaState, 4);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    trans->m_translation += Math::Vec3(x,y,z);

    return 0;
}

int Me::Scripting::Lua_API::Lua_Transform::lua_Rotate(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 4) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    float x = lua_tonumber(a_luaState, 2);
    float y = lua_tonumber(a_luaState, 3);
    float z = lua_tonumber(a_luaState, 4);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    trans->m_rotation += Math::Vec3(x,y,z);

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

    luaL_getmetatable(a_luaState, "VectorMetaTable");
    lua_setmetatable(a_luaState, -2);

    return 1;
}

int Me::Scripting::Lua_API::Lua_Transform::lua_Move(lua_State* a_luaState)
{
    EntityID ent;
    Me::Math::Vec3 move;

    if(lua_gettop(a_luaState) == 4)
    {
        ent = (EntityID)lua_tonumber(a_luaState, 1);
        move.m_x = lua_tonumber(a_luaState, 2);
        move.m_y = lua_tonumber(a_luaState, 3);
        move.m_z = lua_tonumber(a_luaState, 4);
    }
    else if(lua_gettop(a_luaState) == 2)
    {        
        ent = (EntityID)lua_tonumber(a_luaState, 1);

        if(lua_istable(a_luaState, 2))
        {
            lua_pushstring(a_luaState, "x");
            lua_gettable(a_luaState, 2);
            move.m_x = lua_tonumber(a_luaState, -1);

            lua_pushstring(a_luaState, "y");
            lua_gettable(a_luaState, 2);
            move.m_y = lua_tonumber(a_luaState, -1);

            lua_pushstring(a_luaState, "z");
            lua_gettable(a_luaState, 2);
            move.m_z = lua_tonumber(a_luaState, -1);
        }
    }
    else
    {
        return -1;
    }

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    Me::Math::Mat4 transform = Me::Math::Mat4().Rotation(trans->m_rotation);
    
    Me::Math::Vec3 right = transform.GetRight() * move.m_x;
    Me::Math::Vec3 up = transform.GetUp() * move.m_y;
    Me::Math::Vec3 forward = transform.GetForward() * move.m_z;

    Me::Math::Vec3 movement = forward + right + up;
    trans->m_translation = trans->m_translation + (movement);

    return 0;
}

int Me::Scripting::Lua_API::Lua_Transform::lua_SetLocation(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 4) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    float x = lua_tonumber(a_luaState, 2);
    float y = lua_tonumber(a_luaState, 3);
    float z = lua_tonumber(a_luaState, 4);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    trans->m_translation = Math::Vec3(x,y,z);

    return 0;
}

int Me::Scripting::Lua_API::Lua_Transform::lua_SetRotation(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 4) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    float x = lua_tonumber(a_luaState, 2);
    float y = lua_tonumber(a_luaState, 3);
    float z = lua_tonumber(a_luaState, 4);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    trans->m_rotation = Math::Vec3(x,y,z);

    return 0;
}

int Me::Scripting::Lua_API::Lua_Transform::lua_SetScale(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 4) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    float x = lua_tonumber(a_luaState, 2);
    float y = lua_tonumber(a_luaState, 3);
    float z = lua_tonumber(a_luaState, 4);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    trans->m_scale = Math::Vec3(x,y,z);

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