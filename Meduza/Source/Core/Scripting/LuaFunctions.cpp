#include "MePCH.h"
#include "Core/Scripting/LuaFunctions.h"

#include "MeduzaIncluder.h"

void Me::Scripting::LuaFunctions::RegisterFunctions(lua_State* a_luaState)
{
    lua_register(a_luaState, "_Translate", lua_Translate);
    lua_register(a_luaState, "_SetLocation", lua_SetLocation);
    lua_register(a_luaState, "_Move", lua_Move);
    lua_register(a_luaState, "_Rotate", lua_Rotate);
    lua_register(a_luaState, "_SetRotation", lua_SetRotation);
    lua_register(a_luaState, "_SetScale", lua_SetScale);

    
    lua_register(a_luaState, "_OnKeyUp", lua_OnKeyUp);
    lua_register(a_luaState, "_OnKeyDown", lua_OnKeyDown);
}

int Me::Scripting::LuaFunctions::lua_Translate(lua_State* a_luaState)
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

int Me::Scripting::LuaFunctions::lua_Rotate(lua_State* a_luaState)
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

int Me::Scripting::LuaFunctions::lua_Move(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 4) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    float x = lua_tonumber(a_luaState, 2);
    float y = lua_tonumber(a_luaState, 3);
    float z = lua_tonumber(a_luaState, 4);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);

    Me::Math::Mat4 transform = Me::Math::Mat4().Rotation(trans->m_rotation);
    Me::Math::Vec3 forward = transform.GetForward() * x;
    Me::Math::Vec3 right = transform.GetLeft() * -y;
    Me::Math::Vec3 up = transform.GetUp() * z;

    Me::Math::Vec3 movement = forward + right + up;
    trans->m_translation = trans->m_translation + (movement);

    return 0;
}

int Me::Scripting::LuaFunctions::lua_SetLocation(lua_State* a_luaState)
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

int Me::Scripting::LuaFunctions::lua_SetRotation(lua_State* a_luaState)
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

int Me::Scripting::LuaFunctions::lua_SetScale(lua_State* a_luaState)
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

int Me::Scripting::LuaFunctions::lua_OnKeyUp(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 1) return -1;

    Me::Event::KeyCode key = (Me::Event::KeyCode)lua_tonumber(a_luaState, -1);

    if(Event::EventSystem::GetEventSystem()->KeyUp(key))
    {
        lua_pushnumber(a_luaState, 1);        
    }
    else
    {
        lua_pushnumber(a_luaState, 0); 
    }

    return 1;
}

int Me::Scripting::LuaFunctions::lua_OnKeyDown(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 1) return -1;

    Me::Event::KeyCode key = (Me::Event::KeyCode)lua_tonumber(a_luaState, -1);

    if(Event::EventSystem::GetEventSystem()->KeyDown(key))
    {
        lua_pushnumber(a_luaState, 1);        
    }
    else
    {
        lua_pushnumber(a_luaState, 0); 
    }

    return 1;
}