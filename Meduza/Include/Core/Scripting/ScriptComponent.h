#pragma once

#include "ECS/BaseComponent.h"
#include "ECS/EntityTypes.h"

namespace Me
{    
    namespace Scripting
    {
        struct ScriptComponent : BaseComponent
        { 
            std::string m_script;
            lua_State *m_luaScript;

            static ComponentID s_componentID;

            void Init()
            {
                m_luaScript = luaL_newstate();
                luaL_openlibs(m_luaScript);
                int state = luaL_dofile(m_luaScript, m_script.c_str());

                if(state != 0)
                {
                    ME_LOG("WARNING Something went wrong initing %s \n", m_script.c_str());
                }
            }
        };
    }
}