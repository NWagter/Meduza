#pragma once

namespace Me
{
    namespace Scripting
    {
        class LuaFunctions
        {
            public:
                static void RegisterFunctions(lua_State*);

                static int lua_DestroyEnt(lua_State*);

                // Transform
                static int lua_Translate(lua_State*);
                static int lua_Rotate(lua_State*);

                static int lua_Move(lua_State*);
                
                static int lua_SetLocation(lua_State*);
                static int lua_SetRotation(lua_State*);
                static int lua_SetScale(lua_State*);

                static int lua_OnKeyUp(lua_State*);
                static int lua_OnKeyDown(lua_State*);

                // Collision
                static int lua_OnTriggerEntityName(lua_State*);
                static int lua_OnCollisionEntityName(lua_State*);

                static int lua_InstantiatePrefab(lua_State*);
        };
    }
}