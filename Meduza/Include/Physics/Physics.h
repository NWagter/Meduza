#pragma once

#include "Math/MeduzaMath.h"
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
            Cirlce = 0,
            Sphere,
            Box2D,
            Box3D
        };
        

        using CollisionLayerID = uint16_t;

        struct Ray
        {
            Math::Vec3 m_origin;
            Math::Vec3 m_direction;
        };

        struct CollisionData
        {
            EntityID m_entity;
            CollisionLayerID m_collisionLayerID;
            Math::Vec3 m_hitPoint;
            Math::Vec3 m_hitNormal;
        };
    }
}