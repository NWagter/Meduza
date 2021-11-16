#pragma once

namespace Me
{
    namespace Physics
    {
        struct TriggerResult;
        struct CollisionResult;
    }

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

                    static int lua_OnTrigger(lua_State*);
                    static int lua_OnCollision(lua_State*);

                    static void TriggerResult(lua_State*, Physics::TriggerResult&);
                    static void CollisionResult(lua_State*, Physics::CollisionResult);
            }; 
        
        }
    }
}