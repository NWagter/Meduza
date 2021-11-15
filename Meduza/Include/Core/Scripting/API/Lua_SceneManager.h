#pragma once

namespace Me
{
    namespace Scripting
    {
        namespace Lua_API
        {
            class Lua_SceneManager
            {
            public:
                static void RegisterSceneManagerFunctions(lua_State*);

            private:
                static bool LoadScene(lua_State*, std::string&);
                static int lua_LoadScene(lua_State*);
                static int lua_LoadCleanScene(lua_State*);
            };
        }
    }
}