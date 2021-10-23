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
                Destroy();

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
            void Destroy()
            {
                for(auto lS : m_luastates)
                {
                    lua_getglobal(lS, "OnDestroy");
            
                    if(lua_isfunction(lS, -1) )
                    {
                        lua_pcall(lS,0,0,0);
                    }

                    lua_close(lS);
                }

                m_luastates.clear();
            }
            void AddScript(std::string a_script = "")
            {
                m_scripts.push_back(a_script);
            }
            void RemoveScript(size_t a_id)
            {
                m_scripts.erase(m_scripts.begin() + a_id);
            }
            
            ~ScriptComponent()
            {
                Destroy();
            }
        
        };
    }
}