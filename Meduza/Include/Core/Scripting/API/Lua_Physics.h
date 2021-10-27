#pragma once

namespace Me
{
    namespace Scripting
    {
        namespace Lua_API
        {
            class Lua_Physics
            {
                public:
                    static void RegisterPhysicsFunctions(lua_State*);
                    
                private:
                    static int lua_GetVelocity(lua_State*);
                    static int lua_ApplyForce(lua_State*);

                    static int lua_OnTriggerEntityName(lua_State*);
                    static int lua_OnCollisionEntityName(lua_State*);                 
            }; 
        
        }
    }
}