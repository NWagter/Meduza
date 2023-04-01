#pragma once

#include "Math/Math.h"

using ComponentID = uint64_t;

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
        struct Ray;

        class Collision
        {
        public:

            static bool CheckCollision(PhysicsComponent const* a_physics[2], ColliderComponent const* a_colliders[2], ComponentID const a_componentIds[2], CollisionData& a_data);
            static bool RayIntersection(Ray const* a_ray, PhysicsComponent const* a_physic, ColliderComponent const* a_collider, CollisionData& a_data);

            // ==== AABB collision Checks
            static bool AABB_Box2DToBox2D(PhysicsComponent const* a_physics[2], BoxCollider2DComponent const* a_colliders[2], CollisionData& a_data);
            static bool AABB_Box3DToBox3D(PhysicsComponent const* a_physics[2], BoxCollider3DComponent const* a_colliders[2], CollisionData& a_data);
            static bool AABB_Box3DToSphere(PhysicsComponent const* a_physics[2], BoxCollider3DComponent const* a_boxColl, SphereColliderComponent const* a_sphereColl, CollisionData& a_data);
            static bool AABB_SphereToBox3D(PhysicsComponent const* a_physics[2], SphereColliderComponent const* a_sphereColl, BoxCollider3DComponent const* a_boxColl, CollisionData& a_data);
            static bool SphereToSphere(PhysicsComponent const* a_physics[2], SphereColliderComponent const* a_colliders[2], CollisionData& a_data);
          
            static bool AABB_Box2DToCircle(PhysicsComponent const* a_physics[2], BoxCollider2DComponent const* a_boxColl, CircleColliderComponent const* a_cirlceCol, CollisionData& a_data);
            static bool AABB_CircleToBox2D(PhysicsComponent const* a_physics[2], CircleColliderComponent const* a_cirlceCol, BoxCollider2DComponent const* a_boxColl, CollisionData& a_data);
            static bool CircleToCircle(PhysicsComponent const* a_physics[2], CircleColliderComponent const* a_colliders[2], CollisionData& a_data);
 
        }; 
    }
}