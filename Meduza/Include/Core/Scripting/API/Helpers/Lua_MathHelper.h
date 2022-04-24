#pragma once

namespace Me
{
    struct Value;

    namespace Scripting
    {
        namespace Lua_API
        {
            class Lua_MathHelper
            {
            public:
                static void CreateVector3(lua_State* a_luaState, Math::Vec3 a_vec);
                static Math::Vec3 GetVector3(lua_State* a_luaState, int a_id);

                static void CreateColour(lua_State* a_luaState, Colour a_colour);
                static Colour GetColour(lua_State* a_luaState, int a_id);
            };

        }
    }
}