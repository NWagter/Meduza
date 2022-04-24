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
                    static void RegisterMathFunctions(lua_State* a_luaState);

                private:
                    static int lua_CreateVector3(lua_State* a_luaState);
                    static int lua_GetDistance(lua_State* a_luaState);

                    static int Add_Vec3(lua_State* a_luaState);
                    static int Sub_Vec3(lua_State* a_luaState);
                    static int Mul_Vec3(lua_State* a_luaState);
            }; 
        
        }
    }
}