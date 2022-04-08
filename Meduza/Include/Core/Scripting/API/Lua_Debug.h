#pragma once

namespace Me
{
    namespace Scripting
    {
        namespace Lua_API
        {
            class Lua_Debug
            {
            public:
                static void RegisterEntityFunctions(lua_State* a_luaState);

            private:
                static int lua_Assert(lua_State* a_luaState);
                static int lua_LogError(lua_State* a_luaState);
                static int lua_LogWarning(lua_State* a_luaState);
                static int lua_Log(lua_State* a_luaState);
            };

        }
    }
}