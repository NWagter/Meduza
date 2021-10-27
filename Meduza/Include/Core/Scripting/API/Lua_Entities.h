#pragma once

namespace Me
{
    namespace Scripting
    {
        namespace Lua_API
        {
            class Lua_Entities
            {
                public:
                    static void RegisterEntityFunctions(lua_State*);
                    
                private:
                    static int lua_GetEntityByName(lua_State*);
                    static int lua_DestroyEnt(lua_State*);
            }; 
        
        }
    }
}