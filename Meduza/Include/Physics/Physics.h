#pragma once

#include "Math/MeduzaMath.h"

namespace Me
{
    namespace Physics
    {
        enum class CollisionType
        {
            Overlap,
            Block
        };

        enum class BodyType
        {
            Cirlce,
            Box2D
        };

        struct CollisionData
        {
            Math::Vec3 m_position;
        };

        struct PhysicsBody
        {
            Math::Vec3 m_position = Math::Vec3(0,0,0);
            Math::Vec3 m_rotation = Math::Vec3(0,0,0);
            float m_uniformScale = 1;

            BodyType m_bodyType;

            PhysicsBody(BodyType a_type)
            {
                m_bodyType = a_type;
            }
        };

        struct BodyBox2D : public PhysicsBody
        {
            Me::Math::Vec2 m_size;

            BodyBox2D() : PhysicsBody(BodyType::Box2D) {}
        };

        struct BodyCircle : public PhysicsBody
        {
            float m_radius = 1.0f;

            BodyCircle() : PhysicsBody(BodyType::Cirlce){}
        };
    }
}