#pragma once

namespace Me
{
    namespace Scripting
    {
        namespace Lua_API
        {
            class Lua_Prefabs
            {
                public:
                    static void RegisterPrefabsFunctions(lua_State*);
                    
                private:
                    static int lua_InstantiatePrefab(lua_State*);               
            }; 
        
        }
    }
}