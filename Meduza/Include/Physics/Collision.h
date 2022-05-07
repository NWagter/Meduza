#pragma once

#include "Math/Math.h"

using ComponentID = uint32_t;

namespace Me
{
    namespace Physics
    {
        struct CollisionData;
        struct PhysicsComponent;
        struct ColliderComponent;
        struct BoxCollider2DComponent;
        struct CircleColliderComponent;
        struct BoxCollider3DComponent;
        struct SphereColliderComponent;

        class Collision
        {
        public:

            static bool AABB_CheckCollision(PhysicsComponent* a_physics[2], ColliderComponent* a_colliders[2], ComponentID a_componentIds[2], CollisionData& a_data);

            // ==== AABB collision Checks
            static bool AABB_Box2DToBox2D(PhysicsComponent* a_physics[2], BoxCollider2DComponent* a_colliders[2], CollisionData& a_data);
            static bool AABB_Box3DToBox3D(PhysicsComponent* a_physics[2], BoxCollider3DComponent* a_colliders[2], CollisionData& a_data);
            static bool AABB_Box3DToSphere(PhysicsComponent* a_physics[2], BoxCollider3DComponent* a_boxColl, SphereColliderComponent* a_sphereColl, CollisionData& a_data);
            static bool AABB_SphereToBox3D(PhysicsComponent* a_physics[2], SphereColliderComponent* a_sphereColl, BoxCollider3DComponent* a_boxColl, CollisionData& a_data);
            static bool SphereToSphere(PhysicsComponent* a_physics[2], SphereColliderComponent* a_colliders[2], CollisionData& a_data);
          
            static bool AABB_Box2DToCircle(PhysicsComponent* a_physics[2], BoxCollider2DComponent* a_boxColl, CircleColliderComponent* a_cirlceCol, CollisionData& a_data);
            static bool AABB_CircleToBox2D(PhysicsComponent* a_physics[2], CircleColliderComponent* a_cirlceCol, BoxCollider2DComponent* a_boxColl, CollisionData& a_data);
            static bool CircleToCircle(PhysicsComponent* a_physics[2], CircleColliderComponent* a_colliders[2], CollisionData& a_data);
 
        }; 
    }
}