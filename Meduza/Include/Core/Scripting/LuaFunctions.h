#pragma once

namespace Me
{
    namespace Scripting
    {
        class LuaFunctions
        {
            public:
                static void RegisterFunctions(lua_State* a_luaState);

                static int lua_CallFunction(lua_State* a_luaState);
        };
    }
}