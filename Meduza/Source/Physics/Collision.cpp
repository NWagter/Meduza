#include "MePCH.h"
#include "Physics/Collision.h"

#include "Physics/Physics.h"

#include "Physics/Components/PhysicsComponent.h"
#include "Physics/Components/ColliderComponent.h"
#include "Physics/Components/BoxCollider2DComponent.h"
#include "Physics/Components/BoxCollider3DComponent.h"


bool Me::Physics::Collision::CheckCollision(PhysicsComponent* a_physics[2], ColliderComponent* a_colliders[2], ComponentID a_componentIds[2], CollisionData& a_data)
{
    BodyType types[2];
    
    for(int i = 0; i < 2;i++)
    {
        switch (a_componentIds[i])
        {
        case Components::BoxCollider2D:
            types[i] = BodyType::Box2D;
            break;
        case Components::BoxCollider3D:
            types[i] = BodyType::Box3D;
            break;
        }
    }

    if(types[0] == BodyType::Box2D && types[1] == BodyType::Box2D)
    {
        BoxCollider2DComponent* colliders[2] =
        {
            static_cast<BoxCollider2DComponent*>(a_colliders[0]),
            static_cast<BoxCollider2DComponent*>(a_colliders[1])
        };

        return Box2DToBox2D(a_physics, colliders, a_data);
    }

    return false;
}

bool Me::Physics::Collision::Box2DToBox2D(PhysicsComponent* a_physics[2], BoxCollider2DComponent* a_colliders[2], CollisionData& a_data)
{

    // box2d to box2d collision check
    Math::Vec3 sPos = a_physics[0]->m_position + a_colliders[0]->m_colliderOffset;
    Math::Vec2 sSize = a_colliders[0]->m_colliderSize;

    Math::Vec3 oPos = a_physics[1]->m_position + a_colliders[1]->m_colliderOffset;
    Math::Vec2 oSize = a_colliders[1]->m_colliderSize;

    if((sPos.m_x < oPos.m_x + oSize.m_x)
        && (sPos.m_x + sSize.m_x > oPos.m_x)
        && (sPos.m_y < oPos.m_y + oSize.m_y)
        && (sPos.m_y + sSize.m_y > oPos.m_y))
    {
        
        a_data.m_hitNormal = (sPos - oPos).Normalize();

        return true;
    }
     

    return false;
}