#pragma once

#include "Math/Math.h"
#include "ECS/EntityTypes.h"

namespace Me
{
    namespace Physics
    {
        static constexpr float gs_gravity = 9.8f;
        static constexpr float gs_dragExponent = 1.5f;

        enum class CollisionType : uint16_t
        {
            Overlap = 0,
            Block
        };

        enum class BodyType : uint16_t
        {
            Unkown = 0,
            Cirlce,
            Sphere,
            Box2D,
            Box3D
        };
        

        using CollisionLayerID = uint16_t;

        struct Ray
        {
            Math::Vector3 m_origin;
            Math::Vector3 m_direction;
        };

        struct CollisionData
        {
            EntityID m_entity;
            CollisionLayerID m_collisionLayerID;

            Math::Vector3 m_otherPosition;
            Math::Vector3 m_hitPoint;
            Math::Vector3 m_hitNormal;

            CollisionData()
            {
                m_entity = 0;
            }
        };

        struct TriggerResult
        {
            CollisionData m_data;
            std::string m_name;
            bool m_hit;
        };        
        
        struct CollisionResult
        {
            CollisionData m_data;
            std::string m_name;
            bool m_hit;
        };

        class PhysicsHelper
        {
        public:
            static Math::Vector3 GetFurthestPointInDirection(Math::Matrix4 const& a_transform, Math::Vector3 const& a_direction, std::vector<Math::Vector3> const& a_points);
        };
    }
}