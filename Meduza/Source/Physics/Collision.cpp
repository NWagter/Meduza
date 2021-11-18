#include "MePCH.h"
#include "Physics/Collision.h"

#include "Physics/Physics.h"

#include "Physics/Components/PhysicsComponent.h"
#include "Physics/Components/ColliderComponent.h"
#include "Physics/Components/BoxCollider2DComponent.h"
#include "Physics/Components/CircleColliderComponent.h"
#include "Physics/Components/BoxCollider3DComponent.h"
#include "Physics/Components/SphereColliderComponent.h"


bool Me::Physics::Collision::AABB_CheckCollision(PhysicsComponent* a_physics[2], ColliderComponent* a_colliders[2], ComponentID a_componentIds[2], CollisionData& a_data)
{
    BodyType types[2] = { BodyType::Unkown, BodyType::Unkown};
    
    for(int i = 0; i < 2;i++)
    {
        switch (static_cast<Components>(a_componentIds[i]))
        {
        case Components::BoxCollider2D:
            types[i] = BodyType::Box2D;
            break;
        case Components::BoxCollider3D:
            types[i] = BodyType::Box3D;
            break;
        case Components::CircleCollider:
            types[i] = BodyType::Cirlce;
            break;
        case Components::SphereCollider:
            types[i] = BodyType::Sphere;
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

        return AABB_Box2DToBox2D(a_physics, colliders, a_data);
    }
    if(types[0] == BodyType::Box2D && types[1] == BodyType::Cirlce)
    {
        return AABB_Box2DToCircle(a_physics, static_cast<BoxCollider2DComponent*>(a_colliders[0]), static_cast<CircleColliderComponent*>(a_colliders[1]), a_data);
    }    
    if(types[0] == BodyType::Cirlce && types[1] == BodyType::Box2D)
    {
        return AABB_CircleToBox2D(a_physics, static_cast<CircleColliderComponent*>(a_colliders[0]), static_cast<BoxCollider2DComponent*>(a_colliders[1]), a_data);
    }    
    if(types[0] == BodyType::Cirlce && types[1] == BodyType::Cirlce)
    {
        CircleColliderComponent* colliders[2] =
        {
            static_cast<CircleColliderComponent*>(a_colliders[0]),
            static_cast<CircleColliderComponent*>(a_colliders[1])
        };

        return CircleToCircle(a_physics, colliders, a_data);
    }
    if(types[0] == BodyType::Box3D && types[1] == BodyType::Box3D)
    {
        BoxCollider3DComponent* colliders[2] =
        {
            static_cast<BoxCollider3DComponent*>(a_colliders[0]),
            static_cast<BoxCollider3DComponent*>(a_colliders[1])
        };

        return AABB_Box3DToBox3D(a_physics, colliders, a_data);
    } 
    if(types[0] == BodyType::Box3D && types[1] == BodyType::Sphere)
    {
        return AABB_Box3DToSphere(a_physics, static_cast<BoxCollider3DComponent*>(a_colliders[0]), static_cast<SphereColliderComponent*>(a_colliders[1]), a_data);
    }
    if(types[0] == BodyType::Sphere && types[1] == BodyType::Box3D)
    {
        return AABB_SphereToBox3D(a_physics, static_cast<SphereColliderComponent*>(a_colliders[0]), static_cast<BoxCollider3DComponent*>(a_colliders[1]), a_data);
    }
    if(types[0] == BodyType::Sphere && types[1] == BodyType::Sphere)
    {
        SphereColliderComponent* colliders[2] =
        {
            static_cast<SphereColliderComponent*>(a_colliders[0]),
            static_cast<SphereColliderComponent*>(a_colliders[1])
        };

        return SphereToSphere(a_physics, colliders, a_data);
    }

    return false;
}

bool Me::Physics::Collision::AABB_Box2DToBox2D(PhysicsComponent* a_physics[2], BoxCollider2DComponent* a_colliders[2], CollisionData& a_data)
{
    // box2d to box2d collision check
    Math::Vec3 sPos = (a_physics[0]->m_position + a_physics[0]->m_movement) + a_colliders[0]->m_colliderOffset;
    sPos.m_z = 0;
    Math::Vec2 sHalfSize = a_colliders[0]->m_colliderSize / 2;
    
    Math::Vec3 oPos = (a_physics[1]->m_position + a_physics[1]->m_movement) + a_colliders[1]->m_colliderOffset;
    oPos.m_z = 0;
    Math::Vec2 oHalfSize = a_colliders[1]->m_colliderSize / 2;

    if((sPos.m_x - sHalfSize.m_x <= oPos.m_x + oHalfSize.m_x 
        && sPos.m_x + sHalfSize.m_x >= oPos.m_x - oHalfSize.m_x) &&
        (sPos.m_y - sHalfSize.m_y <= oPos.m_y + oHalfSize.m_y 
        && sPos.m_y + sHalfSize.m_y >= oPos.m_y - oHalfSize.m_y))
    {

        float x = std::max(oPos.m_x - oHalfSize.m_x, std::min(sPos.m_x, oPos.m_x + oHalfSize.m_x));
        float y = std::max(oPos.m_y - oHalfSize.m_y, std::min(sPos.m_y, oPos.m_y + oHalfSize.m_y));
        float z = 0;

        a_data.m_otherPosition = oPos;
        a_data.m_hitPoint = Math::Vec3(x, y, z);
        a_data.m_hitNormal = (sPos - a_data.m_hitPoint).Normalize();

        return true;
    }
     

    return false;
}

bool Me::Physics::Collision::AABB_Box2DToCircle(PhysicsComponent* a_physics[2], BoxCollider2DComponent* a_boxColl, CircleColliderComponent* a_cirlceCol, CollisionData& a_data)
{
    Math::Vec3 sPos = (a_physics[0]->m_position + a_physics[0]->m_movement) + a_boxColl->m_colliderOffset;
    Math::Vec2 sHalfSize = a_boxColl->m_colliderSize / 2;
    sPos.m_z = 0;

    Math::Vec3 circlePos = (a_physics[1]->m_position + a_physics[1]->m_movement) + a_cirlceCol->m_colliderOffset;
    circlePos.m_z = 0;

    float x = std::max(sPos.m_x - sHalfSize.m_x, std::min(circlePos.m_x, sPos.m_x + sHalfSize.m_x));
    float y = std::max(sPos.m_y - sHalfSize.m_y, std::min(circlePos.m_y, sPos.m_y + sHalfSize.m_y));

    a_data.m_hitPoint = Math::Vec3(x, y, 0);
    float distance = Math::Distance(a_data.m_hitPoint, circlePos);

    bool col = distance <= a_cirlceCol->m_radius;

    if (col)
    {
        a_data.m_otherPosition = circlePos;
        a_data.m_hitNormal = (sPos - a_data.m_hitPoint).Normalize();
    }

    return col;
}

bool Me::Physics::Collision::AABB_CircleToBox2D(PhysicsComponent* a_physics[2], CircleColliderComponent* a_cirlceCol, BoxCollider2DComponent* a_boxColl, CollisionData& a_data)
{
    Math::Vec3 sPos = (a_physics[1]->m_position + a_physics[1]->m_movement) + a_boxColl->m_colliderOffset;
    Math::Vec2 sHalfSize = a_boxColl->m_colliderSize / 2;
    sPos.m_z = 0;

    Math::Vec3 circlePos = (a_physics[0]->m_position + a_physics[0]->m_movement) + a_cirlceCol->m_colliderOffset;
    circlePos.m_z = 0;

    float x = std::max(sPos.m_x - sHalfSize.m_x, std::min(circlePos.m_x, sPos.m_x + sHalfSize.m_x));
    float y = std::max(sPos.m_y - sHalfSize.m_y, std::min(circlePos.m_y, sPos.m_y + sHalfSize.m_y));

    a_data.m_hitPoint = Math::Vec3(x, y, 0);
    float distance = Math::Distance(a_data.m_hitPoint, circlePos);

    bool col = distance <= a_cirlceCol->m_radius;

    if (col)
    {
        a_data.m_otherPosition = circlePos;
        a_data.m_hitNormal = (circlePos - a_data.m_hitPoint).Normalize();
    }

    return col;
}

bool Me::Physics::Collision::CircleToCircle(PhysicsComponent* a_physics[2], CircleColliderComponent* a_colliders[2], CollisionData& a_data)
{
    Math::Vec3 sPos = (a_physics[0]->m_position + a_physics[0]->m_movement) + a_colliders[0]->m_colliderOffset;
    Math::Vec3 oPos = (a_physics[1]->m_position + a_physics[1]->m_movement) + a_colliders[1]->m_colliderOffset;

    sPos.m_z = 0;
    oPos.m_z = 0;

    float distance = Math::Distance(sPos, oPos);
    float rad = (a_colliders[0]->m_radius) + (a_colliders[1]->m_radius);

    bool col = distance <= rad;

    if (col)
    {
        a_data.m_otherPosition = oPos;
        a_data.m_hitNormal = (sPos - oPos).Normalize();
    }

    return col;
}

bool Me::Physics::Collision::AABB_Box3DToBox3D(PhysicsComponent* a_physics[2], BoxCollider3DComponent* a_colliders[2], CollisionData& a_data)
{
    Math::Vec3 sPos = (a_physics[0]->m_position + a_physics[0]->m_movement) + a_colliders[0]->m_colliderOffset;
    Math::Vec3 sHalfSize = a_colliders[0]->m_colliderSize / 2;

    Math::Vec3 oPos = (a_physics[1]->m_position + a_physics[1]->m_movement) + a_colliders[1]->m_colliderOffset;
    Math::Vec3 oHalfSize = a_colliders[1]->m_colliderSize / 2;

    if((sPos.m_x - sHalfSize.m_x <= oPos.m_x + oHalfSize.m_x 
        && sPos.m_x + sHalfSize.m_x >= oPos.m_x - oHalfSize.m_x) &&
        (sPos.m_y - sHalfSize.m_y <= oPos.m_y + oHalfSize.m_y 
        && sPos.m_y + sHalfSize.m_y >= oPos.m_y - oHalfSize.m_y) &&
        (sPos.m_z - sHalfSize.m_z <= oPos.m_z + oHalfSize.m_z 
        && sPos.m_z + sHalfSize.m_z >= oPos.m_z - oHalfSize.m_z)) 
    {
        float x = std::max(oPos.m_x - oHalfSize.m_x, std::min(sPos.m_x, oPos.m_x + oHalfSize.m_x));
        float y = std::max(oPos.m_y - oHalfSize.m_y, std::min(sPos.m_y, oPos.m_y + oHalfSize.m_y));
        float z = std::max(oPos.m_z - oHalfSize.m_z, std::min(sPos.m_z, oPos.m_z + oHalfSize.m_z));

        a_data.m_otherPosition = oPos;
        a_data.m_hitPoint = Math::Vec3(x, y, z);
        a_data.m_hitNormal = (sPos - a_data.m_hitPoint).Normalize();

        return true;
    }

    return false;
}

bool Me::Physics::Collision::AABB_Box3DToSphere(PhysicsComponent* a_physics[2], BoxCollider3DComponent* a_boxColl, SphereColliderComponent* a_sphereColl, CollisionData& a_data)
{
    Math::Vec3 sPos = (a_physics[0]->m_position + a_physics[0]->m_movement) + a_boxColl->m_colliderOffset;
    Math::Vec3 sHalfSize = a_boxColl->m_colliderSize / 2;
    
    Math::Vec3 spherePos = (a_physics[1]->m_position + a_physics[1]->m_movement) + a_sphereColl->m_colliderOffset;

    float x = std::max(sPos.m_x - sHalfSize.m_x, std::min(spherePos.m_x, sPos.m_x + sHalfSize.m_x));
    float y = std::max(sPos.m_y - sHalfSize.m_y, std::min(spherePos.m_y, sPos.m_y + sHalfSize.m_y));
    float z = std::max(sPos.m_z - sHalfSize.m_z, std::min(spherePos.m_z, sPos.m_z + sHalfSize.m_z));

    a_data.m_hitPoint = Math::Vec3(x, y, z);
    float distance = Math::Distance(a_data.m_hitPoint, spherePos);

    bool col = distance <= a_sphereColl->m_radius;

    if(col)
    {
        a_data.m_otherPosition = spherePos;
        a_data.m_hitNormal = (sPos - a_data.m_hitPoint).Normalize();
    }
    return col;
}

bool Me::Physics::Collision::AABB_SphereToBox3D(PhysicsComponent* a_physics[2], SphereColliderComponent* a_sphereColl, BoxCollider3DComponent* a_boxColl, CollisionData& a_data)
{
    Math::Vec3 oPos = (a_physics[1]->m_position + a_physics[1]->m_movement) + a_boxColl->m_colliderOffset;
    Math::Vec3 sHalfSize = a_boxColl->m_colliderSize / 2;

    Math::Vec3 spherePos = (a_physics[0]->m_position + a_physics[0]->m_movement) + a_sphereColl->m_colliderOffset;

    float x = std::max(oPos.m_x - sHalfSize.m_x, std::min(spherePos.m_x, oPos.m_x + sHalfSize.m_x));
    float y = std::max(oPos.m_y - sHalfSize.m_y, std::min(spherePos.m_y, oPos.m_y + sHalfSize.m_y));
    float z = std::max(oPos.m_z - sHalfSize.m_z, std::min(spherePos.m_z, oPos.m_z + sHalfSize.m_z));

    a_data.m_hitPoint = Math::Vec3(x, y, z);
    float distance = Math::Distance(a_data.m_hitPoint, spherePos);

    bool col = distance <= a_sphereColl->m_radius;

    if(col)
    {
        a_data.m_otherPosition = oPos;
        a_data.m_hitNormal = (spherePos - a_data.m_hitPoint).Normalize();
    }

    return col;
}

bool Me::Physics::Collision::SphereToSphere(PhysicsComponent* a_physics[2], SphereColliderComponent* a_sphereCollider[2], CollisionData& a_data)
{
    Math::Vec3 sPos = (a_physics[0]->m_position + a_physics[0]->m_movement) + a_sphereCollider[0]->m_colliderOffset;
    Math::Vec3 oPos = (a_physics[1]->m_position + a_physics[1]->m_movement) + a_sphereCollider[1]->m_colliderOffset;

    float distance = Math::Distance(sPos, oPos);    
    float rad = (a_sphereCollider[0]->m_radius) + (a_sphereCollider[1]->m_radius);

    bool col = distance <= rad;

    if(col)
    {
        a_data.m_otherPosition = oPos;
        a_data.m_hitNormal = (sPos - oPos).Normalize();
    }

    return col;
}


