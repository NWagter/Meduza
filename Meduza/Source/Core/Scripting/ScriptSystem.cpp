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
        Start(rC, m_entities[i]);
    }
}

void Me::Scripting::ScriptSystem::OnUpdate(float a_dt)
{
    auto luaScripting = LuaScripting::GetInstance();

    for(int i =0; i < m_entities.size(); i++)
    {
        ScriptComponent* rC = std::get<ScriptComponent*>(m_components[i]);

        if(!rC->m_scripts.empty() && rC->m_luastates.empty())
        {
            Start(rC, m_entities[i]);
        }

        for(auto lScript : rC->m_luastates)
        {
            if(lScript == nullptr)
            {  
                continue;
            }

                      
            lua_getglobal(lScript, "OnUpdate");
    
            if(lua_isfunction(lScript, -1) )
            {
                lua_pushlightuserdata(lScript, this);
                lua_pushnumber(lScript, (uint64_t)m_entities[i]);
                lua_pushnumber(lScript, a_dt);
                lua_pcall(lScript,3,0,0);
            }
        }
    }
}

void Me::Scripting::ScriptSystem::Start(ScriptComponent* a_scriptComponent, EntityID a_entId)
{
    a_scriptComponent->Init();

    for(auto lScript : a_scriptComponent->m_luastates)
    {
        if(lScript != nullptr)
        {
            if(!a_scriptComponent->m_functionsRegistered)
            {
                LuaFunctions::RegisterFunctions(lScript);
            }  

            lua_getglobal(lScript, "OnStart");
    
            if(lua_isfunction(lScript, -1) )
            {
                lua_pushlightuserdata(lScript, this);
                lua_pushnumber(lScript, (uint64_t)a_entId);
                lua_pcall(lScript,2,0,0);
            }
        }
    }   
}