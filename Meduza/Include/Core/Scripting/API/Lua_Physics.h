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
                    static void RegisterPhysicsFunctions(lua_State* a_luaState);
                    
                private:
                    static int lua_GetVelocity(lua_State* a_luaState);
                    static int lua_ApplyForce(lua_State* a_luaState);

                    static int lua_OnTrigger(lua_State* a_luaState);
                    static int lua_OnCollision(lua_State* a_luaState);

                    static void TriggerResult(lua_State* a_luaState, Physics::TriggerResult& a_result);
                    static void CollisionResult(lua_State* a_luaState, Physics::CollisionResult& a_result);
            }; 
        
        }
    }
}