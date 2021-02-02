#pragma once

#include "Math/MeduzaMath.h"

namespace Me
{
    namespace Physics
    {
        static constexpr float gs_Gravity = 9.8f;

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
            Math::Vec3 m_hitPoint;
            Math::Vec3 m_hitNormal;
        };

        struct PhysicsBody
        {
            Math::Vec3 m_position = Math::Vec3(0,0,0);
            Math::Vec3 m_rotation = Math::Vec3(0,0,0);
            float m_uniformScale = 1;

            float m_bodyMass = 10.0f;

            BodyType m_bodyType;

            PhysicsBody(BodyType a_type)
            {
                m_bodyType = a_type;
            }
        };

        struct BodyBox2D : public PhysicsBody
        {
            Me::Math::Vec2 m_size = Me::Math::Vec2(1,1);

            BodyBox2D() : PhysicsBody(BodyType::Box2D) {}
        };

        struct BodyCircle : public PhysicsBody
        {
            float m_radius = 1.0f;

            BodyCircle() : PhysicsBody(BodyType::Cirlce){}
        };
    }
}