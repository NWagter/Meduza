#pragma once

namespace Me
{
    namespace Scripting
    {
        namespace Lua_API
        {
            class Lua_Graphics
            {
                public:
                    static void RegisterGraphicsFunctions(lua_State* a_luaState);
                
                private:
                    static int lua_SetUV(lua_State* a_luaState);
            }; 
        
        }
    }
}