#include "MePCH.h"
#include "Core/Scripting/ScriptSystem.h"
#include "Core/Scripting/LuaScripting.h"

Me::Scripting::ScriptSystem::ScriptSystem()
{
    m_executeMask = EXECUTE_INGAME;
}

Me::Scripting::ScriptSystem::~ScriptSystem()
{
    
}

void Me::Scripting::ScriptSystem::OnUpdate(float)
{
    auto luaScripting = LuaScripting::GetInstance();

    for(auto& compTuple : m_components)
    {
        ScriptComponent* rC = std::get<ScriptComponent*>(compTuple);

        if(!rC->m_script.empty())
        {
            luaScripting->ExecuteScript(rC->m_script);
        }
    }
}