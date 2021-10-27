#pragma once

namespace Me
{
    namespace Scripting
    {
        namespace Lua_API
        {
            class Lua_Events
            {
                public:
                    static void RegisterEventFunctions(lua_State*);
                    
                private:                
                    static int lua_OnKeyUp(lua_State*);
                    static int lua_OnKeyDown(lua_State*);
            }; 
        
        }
    }
}