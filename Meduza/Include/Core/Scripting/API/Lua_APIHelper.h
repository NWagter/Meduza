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
                    static Math::Vec3 GetVector(lua_State*, int);
                    static void StackDump(lua_State*);
            }; 
        
        }
    }
}