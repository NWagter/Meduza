#pragma once

namespace Me
{
    namespace Scripting
    {
        namespace Lua_API
        {
            class Lua_Helper
            {
                public:
                    static Math::Vec3 GetVector3(lua_State* a_luaState, int a_id);
                    static void StackDump(lua_State* a_luaState);
            }; 
        
        }
    }
}