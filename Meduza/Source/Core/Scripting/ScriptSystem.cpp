#include "MePCH.h"
#include "Core/Scripting/ScriptSystem.h"
#include "Core/Scripting/LuaScripting.h"

#include "Core/Components/TransformComponent.h"

Me::Scripting::ScriptSystem::ScriptSystem()
{
    m_executeMask = EXECUTE_INGAME;
}

Me::Scripting::ScriptSystem::~ScriptSystem()
{
    
}

static int wrap_SetLocation(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 4) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    float x = lua_tonumber(a_luaState, 2);
    float y = lua_tonumber(a_luaState, 3);
    float z = lua_tonumber(a_luaState, 4);

    auto trans =  Me::EntityManager::GetEntityManager()->GetComponent<Me::TransformComponent>(ent);
    trans->m_translation = Me::Math::Vec3(x,y,z);
}

void Me::Scripting::ScriptSystem::OnUpdate(float a_dt)
{
    auto luaScripting = LuaScripting::GetInstance();

    for(int i =0; i < m_entities.size(); i++)
    {
        ScriptComponent* rC = std::get<ScriptComponent*>(m_components[i]);

        if(rC->m_luaScript != nullptr)
        {
            lua_getglobal(rC->m_luaScript, "OnUpdate");
            lua_register(rC->m_luaScript, "_SetLocation", wrap_SetLocation);
    
            if(lua_isfunction(rC->m_luaScript, -1) )
            {
                lua_pushlightuserdata(rC->m_luaScript, this);
                lua_pushnumber(rC->m_luaScript, (uint64_t)m_entities[i]);
                lua_pushnumber(rC->m_luaScript, a_dt);
                lua_pcall(rC->m_luaScript,3,0,0);
            }
        }
    }
}