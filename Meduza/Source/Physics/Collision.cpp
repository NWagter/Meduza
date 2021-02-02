#include "MePCH.h"
#include "Physics/Collision.h"

#include "Physics/Physics.h"
#include "Core/Components/PhysicsComponent.h"

bool Me::Physics::Collision::CheckCollision(PhysicsBody* a_self, PhysicsBody* a_other, CollisionData& a_data)
{

    if(a_self->m_bodyType == BodyType::Box2D && a_other->m_bodyType == BodyType::Box2D)
    {
        return Box2DToBox2D(static_cast<BodyBox2D*>(a_self), static_cast<BodyBox2D*>(a_other), a_data);
    }
    else if(a_self->m_bodyType == BodyType::Box2D && a_other->m_bodyType == BodyType::Cirlce)
    {
        return Box2DToCircle(static_cast<BodyBox2D*>(a_self), static_cast<BodyCircle*>(a_other), a_data);
    }
    else if(a_self->m_bodyType == BodyType::Cirlce && a_other->m_bodyType == BodyType::Box2D)
    {
        return CircleToBox2D(static_cast<BodyCircle*>(a_self), static_cast<BodyBox2D*>(a_other), a_data);
    }
    else if(a_self->m_bodyType == BodyType::Cirlce && a_other->m_bodyType == BodyType::Cirlce)
    {
        return CircleToCircle(static_cast<BodyCircle*>(a_self), static_cast<BodyCircle*>(a_other), a_data);
    }


    return false;
}


bool Me::Physics::Collision::Box2DToBox2D(BodyBox2D* a_self, BodyBox2D* a_other, CollisionData& a_data)
{
    // box2d to box2d collision check
    Math::Vec3 sPos = a_self->m_position;
    float sSize = a_self->m_uniformScale;

    Math::Vec3 oPos = a_other->m_position;
    float oSize = a_other->m_uniformScale;

    if((sPos.m_x < oPos.m_x + oSize)
        && (sPos.m_x + sSize > oPos.m_x)
        && (sPos.m_y < oPos.m_y + oSize)
        && (sPos.m_y + sSize > oPos.m_y))
    {
        
        a_data.m_hitNormal = (sPos - oPos).Normalize();

        return true;
    }
        


    return false;
}

bool Me::Physics::Collision::Box2DToCircle(BodyBox2D* a_self, BodyCircle* a_other, CollisionData& a_data)
{
    // box2d to circle collision check

    return false;
}

bool Me::Physics::Collision::CircleToBox2D(BodyCircle* a_self, BodyBox2D* a_other, CollisionData& a_data)
{
    // circle to box2d collision check

    return false;
}

bool Me::Physics::Collision::CircleToCircle(BodyCircle* a_self, BodyCircle* a_other, CollisionData& a_data)
{
    // circle to circle collision check

    return false;
}