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