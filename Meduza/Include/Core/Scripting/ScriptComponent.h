#pragma once

#include "ECS/BaseComponent.h"

namespace Me
{    
    namespace Scripting
    {
        struct ScriptComponent : BaseComponent
        { 
            std::vector<std::string> m_scripts;
            std::vector<lua_State*> m_luastates;

            static ComponentID s_componentID;

            bool m_functionsRegistered;

            void Init()
            {
                for(auto lS : m_luastates)
                {
                    if(lS != nullptr)
                        delete lS;
                }
                m_luastates.clear();

                for(size_t i = 0; i < m_scripts.size(); i++)
                {
                    lua_State* luaState = luaL_newstate();
                    luaL_openlibs(luaState);
                    int state = luaL_dofile(luaState, m_scripts.at(i).c_str());
                    m_functionsRegistered = false;
                    if(state != 0)
                    {
                        ME_LOG("WARNING Something went wrong initing %s \n", m_scripts.at(i).c_str());
                    }

                    m_luastates.push_back(luaState);
                }
            }
            void AddScript(std::string a_script = "")
            {
                m_scripts.push_back(a_script);
            }
            void RemoveScript(size_t a_id)
            {
                m_scripts.erase(m_scripts.begin() + a_id);
            }
        
        };
    }
}