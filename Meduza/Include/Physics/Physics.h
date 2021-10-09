#pragma once

#include "Math/MeduzaMath.h"
#include "ECS/EntityTypes.h"

namespace Me
{
    namespace Physics
    {
        static constexpr float gs_gravity = 9.8f;

        enum class CollisionType : uint16_t
        {
            Overlap = 0,
            Block
        };

        enum class BodyType : uint16_t
        {
            Cirlce = 0,
            Box2D,
            Box3D
        };
        

        using PhysicsLayerID = uint16_t;

        struct Ray
        {
            Math::Vec3 m_origin;
            Math::Vec3 m_direction;
        };

        struct CollisionData
        {
            EntityID m_entity;
            PhysicsLayerID m_physicsLayerId;
            Math::Vec3 m_hitPoint;
            Math::Vec3 m_hitNormal;
        };

        struct PhysicsBody
        {
            Math::Vec3 m_position = Math::Vec3(0,0,0);
            Math::Vec3 m_rotation = Math::Vec3(0,0,0);
            float m_uniformScale = 1;

            float m_bodyMass = 10.0f;
            float m_gravity;

            BodyType m_bodyType;

            PhysicsBody(BodyType a_type)
            {
                m_bodyType = a_type;
                m_gravity = gs_gravity;
            }
        };

        struct BodyBox2D : public PhysicsBody
        {
            Me::Math::Vec2 m_size = Me::Math::Vec2(1,1);

            BodyBox2D() : PhysicsBody(BodyType::Box2D) {}
            BodyBox2D(Me::Math::Vec2 a_size) : PhysicsBody(BodyType::Box2D) 
            {
                m_size = a_size;
            }
        };

        struct BodyCircle : public PhysicsBody
        {
            float m_radius = 1.0f;

            BodyCircle() : PhysicsBody(BodyType::Cirlce){}
            BodyCircle(float a_radius) : PhysicsBody(BodyType::Cirlce) 
            {
                m_radius = a_radius;
            }
        };
    
        struct BodyBox3D : public PhysicsBody
        {
            Me::Math::Vec3 m_size = Me::Math::Vec3(1,1,1);

            BodyBox3D() : PhysicsBody(BodyType::Box3D) {}
            
            BodyBox3D(Me::Math::Vec3 a_size) : PhysicsBody(BodyType::Box3D)
            {
                m_size = a_size;
            }
        };
    }
}