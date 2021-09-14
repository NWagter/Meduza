#pragma once

namespace Me
{
    namespace Scripting
    {
        class LuaFunctions
        {
            public:
                static void RegisterFunctions(lua_State*);

                static int lua_Translate(lua_State*);
                static int lua_Rotate(lua_State*);
                
                static int lua_SetLocation(lua_State*);
                static int lua_SetPositionX(lua_State*);
                static int lua_SetRotation(lua_State*);
                static int lua_SetScale(lua_State*);
        };
    }
}