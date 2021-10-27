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
                    static void RegisterTransformFunctions(lua_State*);

                private:                
                    static int lua_Translate(lua_State*);
                    static int lua_Rotate(lua_State*);

                    static int lua_GetLocation(lua_State*);

                    static int lua_Move(lua_State*);
                    
                    static int lua_SetLocation(lua_State*);
                    static int lua_SetRotation(lua_State*);
                    static int lua_SetScale(lua_State*);
                    static int lua_FlipX(lua_State*);
                    static int lua_FlipY(lua_State*);
            }; 
        
        }
    }
}