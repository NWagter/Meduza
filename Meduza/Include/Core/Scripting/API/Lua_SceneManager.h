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
                static void RegisterSceneManagerFunctions(lua_State* a_luaState);

            private:
                static bool LoadScene(lua_State* a_luaState, std::string& a_scene);
                static int lua_LoadScene(lua_State* a_luaState);
                static int lua_LoadCleanScene(lua_State* a_luaState);
            };
        }
    }
}