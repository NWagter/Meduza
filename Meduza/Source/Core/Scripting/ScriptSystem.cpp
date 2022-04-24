#include "MePCH.h"
#include "Core/Scripting/ScriptSystem.h"
#include "Core/Scripting/LuaScripting.h"
#include "Core/Scripting/LuaFunctions.h"
#include "Core/Scripting/API/Helpers/Lua_APIHelper.h"

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
    ME_PROFILE_FUNC("ScriptingSystem");

    auto luaScripting = LuaScripting::GetInstance();

    for(int i =0; i < m_entities.size(); i++)
    {
        ScriptComponent* rC = std::get<ScriptComponent*>(m_components[i]);


        if(!rC->m_scripts.empty() && !rC->m_inited)
        {
            Start(rC, m_entities[i]);
        }

        for(auto script : rC->m_scripts)
        {
            if(script->m_luaState == nullptr)
            {  
                continue;
            }

            auto lScript = script->m_luaState;
                      
            lua_getglobal(lScript, "OnUpdate");
    
            if(lua_isfunction(lScript, -1) )
            {
                lua_pushlightuserdata(lScript, this);
                lua_pushnumber(lScript, (uint32_t)m_entities[i]);
                lua_pushnumber(lScript, a_dt);
                if (lua_pcall(lScript, 3, 0, 0) != LUA_OK)
                {
                    std::string error = lua_tostring(lScript, -1);
                    ME_LUA_ERROR("%s \n", error.c_str());
                    // Stop the game? Pause the Game?
                }
            }
        }
    }
}

void Me::Scripting::ScriptSystem::Start(ScriptComponent* a_scriptComponent, EntityID a_entId)
{
    a_scriptComponent->Init();

    for(auto script : a_scriptComponent->m_scripts)
    {
        if(script->m_luaState != nullptr)
        {
            auto lScript = script->m_luaState;

            if(!a_scriptComponent->m_functionsRegistered)
            {
                LuaFunctions::RegisterFunctions(lScript);
            }  

            lua_getglobal(lScript, "OnStart");
    
            if(lua_isfunction(lScript, -1) )
            {
                lua_pushlightuserdata(lScript, this);
                lua_pushnumber(lScript, (uint32_t)a_entId);
                Lua_API::Lua_Helper::CreateInitializationTable(lScript, script->m_inputFields);
                lua_pcall(lScript,3,0,0);
            }
        }
    }   
}