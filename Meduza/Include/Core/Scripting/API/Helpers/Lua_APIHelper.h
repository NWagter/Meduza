#pragma once

namespace Me
{
    struct Value;

    namespace Scripting
    {
        namespace Lua_API
        {
            class Lua_Helper
            {
                public:
                    static void CreateInitializationTable(lua_State* a_luaState, std::vector<Value*> a_values);
                    static void StackDump(lua_State* a_luaState);
            }; 
        
        }
    }
}