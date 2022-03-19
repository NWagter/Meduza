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
                    static void RegisterEntityFunctions(lua_State* a_luaState);
                    
                private:
                    static int lua_GetEntityByName(lua_State* a_luaState);
                    static int lua_DoesEntityExist(lua_State* a_luaState);
                    static int lua_DestroyEnt(lua_State* a_luaState);
            }; 
        
        }
    }
}