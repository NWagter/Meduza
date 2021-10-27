#pragma once

namespace Me
{
    namespace Scripting
    {
        namespace Lua_API
        {
            class Lua_Math
            {
                public:
                    static void RegisterMathFunctions(lua_State*);
                
                private:
                    static int lua_CreateVector2(lua_State*);
                    static int lua_CreateVector3(lua_State*);
                    
                    static int lua_GetDistance(lua_State*);
            }; 
        
        }
    }
}