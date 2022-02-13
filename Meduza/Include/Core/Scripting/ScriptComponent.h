#pragma once

#include "ECS/BaseComponent.h"
#include "ScriptComponentHelper.h"

namespace Me
{    
    namespace Scripting
    {

        struct ScriptComponent : BaseComponent
        { 
            std::vector<Script*> m_scripts;

            static ComponentID s_componentID;

            bool m_functionsRegistered;
            bool m_inited = false;

            void Init()
            {
                Destroy();

                for (auto script : m_scripts)
                {
                    lua_State* luaState = luaL_newstate();
                    luaL_openlibs(luaState);
                    int state = luaL_dofile(luaState, script->m_script.c_str());
                    m_functionsRegistered = false;
                    m_inited = true;
                    if (state != 0)
                    {
                        ME_LOG("WARNING Something went wrong initing %s \n", script->m_script.c_str());
                    }

                    script->m_luaState = luaState;
                }
            }
            void Destroy()
            {
                for(auto script : m_scripts)
                {
                    if (script->m_luaState == nullptr)
                    {
                        continue;
                    }

                    lua_getglobal(script->m_luaState, "OnDestroy");
            
                    if(lua_isfunction(script->m_luaState, -1) )
                    {
                        lua_pcall(script->m_luaState,0,0,0);
                    }

                    lua_close(script->m_luaState);
                }

                m_inited = false;
            }
            void AddScript(std::string a_script = "")
            {
                m_scripts.push_back(new Script(a_script));
            }
            void RemoveScript(size_t a_id)
            {
                auto comp = m_scripts.at(a_id);
                delete comp;
                m_scripts.erase(m_scripts.begin() + a_id);
            }
            
            ~ScriptComponent()
            {
                Destroy();

                for (size_t i = 0; i < m_scripts.size(); i++)
                {
                    RemoveScript(i);
                }
            }


            virtual bool RenderCustomGUI() { return false; }
            std::string EditorComponentName() override { return "ScriptComponent"; }
        };
    }
}