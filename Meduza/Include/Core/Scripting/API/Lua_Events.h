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
                    static void RegisterEventFunctions(lua_State* a_luaState);
                    
                private:                
                    static int lua_OnKeyUp(lua_State* a_luaState);
                    static int lua_OnKeyDown(lua_State* a_luaState);
            }; 
        
        }
    }
}