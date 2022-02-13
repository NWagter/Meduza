#pragma once

namespace Me
{
    namespace Scripting
    {
        namespace Lua_API
        {
            class Lua_Transform
            {
                public:
                    static void RegisterTransformFunctions(lua_State* a_luaState);

                private:                
                    static int lua_Translate(lua_State* a_luaState);
                    static int lua_Rotate(lua_State* a_luaState);

                    static int lua_GetLocation(lua_State* a_luaState);

                    static int lua_Move(lua_State* a_luaState);
                    static int lua_LookAt(lua_State* a_luaState);
                    
                    static int lua_SetLocation(lua_State* a_luaState);
                    static int lua_SetRotation(lua_State* a_luaState);
                    static int lua_SetScale(lua_State* a_luaState);
                    static int lua_FlipX(lua_State* a_luaState);
                    static int lua_FlipY(lua_State* a_luaState);
            }; 
        
        }
    }
}