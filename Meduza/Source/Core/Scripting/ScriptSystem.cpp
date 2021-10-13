#include "MePCH.h"
#include "Core/Scripting/ScriptSystem.h"
#include "Core/Scripting/LuaScripting.h"
#include "Core/Scripting/LuaFunctions.h"

Me::Scripting::ScriptSystem::ScriptSystem()
{
    m_executeMask = EXECUTE_INGAME;
}

Me::Scripting::ScriptSystem::~ScriptSystem()
{
    
}

void Me::Scripting::ScriptSystem::OnStart()
{
    for(int i =0; i < m_entities.size(); i++)
    {
        ScriptComponent* rC = std::get<ScriptComponent*>(m_components[i]);
        rC->Init();

        if(rC->m_luaScript != nullptr)
        {
            if(!rC->m_functionsRegistered)
            {
                LuaFunctions::RegisterFunctions(rC->m_luaScript);
            }  

            lua_getglobal(rC->m_luaScript, "OnStart");
    
            if(lua_isfunction(rC->m_luaScript, -1) )
            {
                lua_pushlightuserdata(rC->m_luaScript, this);
                lua_pushnumber(rC->m_luaScript, (uint64_t)m_entities[i]);
                lua_pcall(rC->m_luaScript,2,0,0);
            }
        }
    }
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