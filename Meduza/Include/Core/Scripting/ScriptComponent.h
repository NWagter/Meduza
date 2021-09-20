#pragma once

#include "ECS/BaseComponent.h"

namespace Me
{    
    namespace Scripting
    {
        struct ScriptComponent : BaseComponent
        { 
            std::string m_script;
            lua_State *m_luaScript;

            static ComponentID s_componentID;

            bool m_functionsRegistered;

            void Init()
            {
                m_luaScript = luaL_newstate();
                luaL_openlibs(m_luaScript);
                int state = luaL_dofile(m_luaScript, m_script.c_str());
                m_functionsRegistered = false;
                if(state != 0)
                {
                    ME_LOG("WARNING Something went wrong initing %s \n", m_script.c_str());
                }
            }
        };
    }
}