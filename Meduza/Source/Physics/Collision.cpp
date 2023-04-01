#include "MePCH.h"
#include "Physics/Collision.h"

#include "Physics/Physics.h"

#include "Physics/GJKAlgorithm.h"

#include "Physics/Components/PhysicsComponent.h"
#include "Physics/Components/ColliderComponent.h"
#include "Physics/Components/BoxCollider2DComponent.h"
#include "Physics/Components/CircleColliderComponent.h"
#include "Physics/Components/BoxCollider3DComponent.h"
#include "Physics/Components/SphereColliderComponent.h"

#include "Utils/MeduzaDebug.h"

#define USE_GJK 1

bool Me::Physics::Collision::CheckCollision(PhysicsComponent const* a_physics[2], ColliderComponent const* a_colliders[2], ComponentID const a_componentIds[2], CollisionData& a_data)
{
#if USE_GJK
    return Physics::GJKAlgorithm::GJKIntersaction(a_physics, a_colliders, a_data);
#endif // USE_GJK


    BodyType types[2] = { BodyType::Unkown, BodyType::Unkown };

    for (int i = 0; i < 2; i++)
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

    if (types[0] == BodyType::Box2D && types[1] == BodyType::Box2D)
    {
        BoxCollider2DComponent const* colliders[2] =
        {
            static_cast<BoxCollider2DComponent const*>(a_colliders[0]),
            static_cast<BoxCollider2DComponent const*>(a_colliders[1])
        };

        return AABB_Box2DToBox2D(a_physics, colliders, a_data);
    }
    if (types[0] == BodyType::Box2D && types[1] == BodyType::Cirlce)
    {
        return AABB_Box2DToCircle(a_physics, static_cast<BoxCollider2DComponent const*>(a_colliders[0]), static_cast<CircleColliderComponent const*>(a_colliders[1]), a_data);
    }
    if (types[0] == BodyType::Cirlce && types[1] == BodyType::Box2D)
    {
        return AABB_CircleToBox2D(a_physics, static_cast<CircleColliderComponent const*>(a_colliders[0]), static_cast<BoxCollider2DComponent const*>(a_colliders[1]), a_data);
    }
    if (types[0] == BodyType::Cirlce && types[1] == BodyType::Cirlce)
    {
        CircleColliderComponent const* colliders[2] =
        {
            static_cast<CircleColliderComponent const*>(a_colliders[0]),
            static_cast<CircleColliderComponent const*>(a_colliders[1])
        };

        return CircleToCircle(a_physics, colliders, a_data);
    }
    if (types[0] == BodyType::Box3D && types[1] == BodyType::Box3D)
    {
        BoxCollider3DComponent const* colliders[2] =
        {
            static_cast<BoxCollider3DComponent const*>(a_colliders[0]),
            static_cast<BoxCollider3DComponent const*>(a_colliders[1])
        };

        return AABB_Box3DToBox3D(a_physics, colliders, a_data);
    }
    if (types[0] == BodyType::Box3D && types[1] == BodyType::Sphere)
    {
        return AABB_Box3DToSphere(a_physics, static_cast<BoxCollider3DComponent const*>(a_colliders[0]), static_cast<SphereColliderComponent const*>(a_colliders[1]), a_data);
    }
    if (types[0] == BodyType::Sphere && types[1] == BodyType::Box3D)
    {
        return AABB_SphereToBox3D(a_physics, static_cast<SphereColliderComponent const*>(a_colliders[0]), static_cast<BoxCollider3DComponent const*>(a_colliders[1]), a_data);
    }
    if (types[0] == BodyType::Sphere && types[1] == BodyType::Sphere)
    {
        SphereColliderComponent const* colliders[2] =
        {
            static_cast<SphereColliderComponent const*>(a_colliders[0]),
            static_cast<SphereColliderComponent const*>(a_colliders[1])
        };

        return SphereToSphere(a_physics, colliders, a_data);
    }

    return false;
}

bool Me::Physics::Collision::RayIntersection(Ray const* a_ray, PhysicsComponent const* a_physic, ColliderComponent const* a_collider, CollisionData& a_data)
{
    bool triangleIntersection = true;
    switch (static_cast<Components>(a_collider->GetColliderComponentID()))
    {
    case Components::CircleCollider:
    case Components::SphereCollider:
    {
        triangleIntersection = false;
        break;
    }
    default:
        break;
    }

    IntersectionData intersectionData;
    if (triangleIntersection)
    {
        // Triangle intersection

    }
    else
    {
        // Sphere intersection
        intersectionData = RaySphereIntersection(a_ray, a_physic, static_cast<SphereColliderComponent const*>(a_collider));
    }


    Me::Debug::Settings const& debugSettings = Me::Debug::MeduzaDebug::GetDebuggingSettings();
    if (debugSettings.m_rayIntersections && intersectionData.m_intersection)
    {
        Me::Debug::MeduzaDebug::RenderLine(a_ray->m_origin, a_ray->m_direction, 10.0f, Colours::RED);

        Math::Matrix4 transform;
        transform.SetPosition(a_data.m_hitPoint);
        Me::Debug::MeduzaDebug::RenderSphere(transform, debugSettings.m_scaleVertices);
    }

    return intersectionData.m_intersection;
}

Me::Physics::Collision::IntersectionData Me::Physics::Collision::RaySphereIntersection(Ray const* a_ray, PhysicsComponent const* a_physics, SphereColliderComponent const* a_sphereColl)
{
    IntersectionData data;

    Math::Vector3 m = a_ray->m_origin - a_physics->m_transform.GetPosition();
    float b = Math::DotProduct(m, a_ray->m_direction);
    float c = Math::DotProduct(m, m) - a_sphereColl->m_radius * a_sphereColl->m_radius;

    // Exit if r’s origin outside s (c > 0) and r pointing away from s (b > 0) 
    if (c > 0.0f && b > 0.0f) return data;
    float discr = b * b - c;

    // A negative discriminant corresponds to ray missing sphere 
    if (discr < 0.0f) return data;

    // Ray now found to intersect sphere, compute smallest t value of intersection
    float t = -b - std::sqrt(discr);

    // If t is negative, ray started inside sphere so clamp t to zero 
    if (t < 0.0f) t = 0.0f;
    data.m_intersectionPoints = a_ray->m_origin + (a_ray->m_direction * t);

    return data;
}

// ==== AABB collision Checks

bool Me::Physics::Collision::AABB_Box2DToBox2D(PhysicsComponent const* a_physics[2], BoxCollider2DComponent const* a_colliders[2], CollisionData& a_data)
{
    // box2d to box2d collision check
    Math::Vector3 sPos = (a_physics[0]->m_transform.GetPosition() + a_physics[0]->m_movement) + a_colliders[0]->m_colliderOffset;
    sPos.m_z = 0;
    Math::Vector2 sHalfSize = a_colliders[0]->m_colliderSize / 2.f;

    Math::Vector3 oPos = (a_physics[1]->m_transform.GetPosition() + a_physics[1]->m_movement) + a_colliders[1]->m_colliderOffset;
    oPos.m_z = 0;
    Math::Vector2 oHalfSize = a_colliders[1]->m_colliderSize / 2.f;

    if ((sPos.m_x - sHalfSize.m_x <= oPos.m_x + oHalfSize.m_x
        && sPos.m_x + sHalfSize.m_x >= oPos.m_x - oHalfSize.m_x) &&
        (sPos.m_y - sHalfSize.m_y <= oPos.m_y + oHalfSize.m_y
            && sPos.m_y + sHalfSize.m_y >= oPos.m_y - oHalfSize.m_y))
    {

        float x = std::max(oPos.m_x - oHalfSize.m_x, std::min(sPos.m_x, oPos.m_x + oHalfSize.m_x));
        float y = std::max(oPos.m_y - oHalfSize.m_y, std::min(sPos.m_y, oPos.m_y + oHalfSize.m_y));
        float z = 0;

        a_data.m_otherPosition = oPos;
        a_data.m_hitPoint = Math::Vector3(x, y, z);
        a_data.m_hitNormal = (sPos - a_data.m_hitPoint).Normalize();

        return true;
    }


    return false;
}

bool Me::Physics::Collision::AABB_Box2DToCircle(PhysicsComponent const* a_physics[2], BoxCollider2DComponent const* a_boxColl, CircleColliderComponent const* a_cirlceCol, CollisionData& a_data)
{
    Math::Vector3 sPos = (a_physics[0]->m_transform.GetPosition() + a_physics[0]->m_movement) + a_boxColl->m_colliderOffset;
    Math::Vector2 sHalfSize = a_boxColl->m_colliderSize / 2;
    sPos.m_z = 0;

    Math::Vector3 circlePos = (a_physics[1]->m_transform.GetPosition() + a_physics[1]->m_movement) + a_cirlceCol->m_colliderOffset;
    circlePos.m_z = 0;

    float x = std::max(sPos.m_x - sHalfSize.m_x, std::min(circlePos.m_x, sPos.m_x + sHalfSize.m_x));
    float y = std::max(sPos.m_y - sHalfSize.m_y, std::min(circlePos.m_y, sPos.m_y + sHalfSize.m_y));

    a_data.m_hitPoint = Math::Vector3(x, y, 0);
    float distance = Math::Distance(a_data.m_hitPoint, circlePos);

    bool col = distance <= a_cirlceCol->m_radius;

    if (col)
    {
        a_data.m_otherPosition = circlePos;
        a_data.m_hitNormal = (sPos - a_data.m_hitPoint).Normalize();
    }

    return col;
}

bool Me::Physics::Collision::AABB_CircleToBox2D(PhysicsComponent const* a_physics[2], CircleColliderComponent const* a_cirlceCol, BoxCollider2DComponent const* a_boxColl, CollisionData& a_data)
{
    Math::Vector3 sPos = (a_physics[1]->m_transform.GetPosition() + a_physics[1]->m_movement) + a_boxColl->m_colliderOffset;
    Math::Vector2 sHalfSize = a_boxColl->m_colliderSize / 2;
    sPos.m_z = 0;

    Math::Vector3 circlePos = (a_physics[0]->m_transform.GetPosition() + a_physics[0]->m_movement) + a_cirlceCol->m_colliderOffset;
    circlePos.m_z = 0;

    float x = std::max(sPos.m_x - sHalfSize.m_x, std::min(circlePos.m_x, sPos.m_x + sHalfSize.m_x));
    float y = std::max(sPos.m_y - sHalfSize.m_y, std::min(circlePos.m_y, sPos.m_y + sHalfSize.m_y));

    a_data.m_hitPoint = Math::Vector3(x, y, 0);
    float distance = Math::Distance(a_data.m_hitPoint, circlePos);

    bool col = distance <= a_cirlceCol->m_radius;

    if (col)
    {
        a_data.m_otherPosition = circlePos;
        a_data.m_hitNormal = (circlePos - a_data.m_hitPoint).Normalize();
    }

    return col;
}

bool Me::Physics::Collision::CircleToCircle(PhysicsComponent const* a_physics[2], CircleColliderComponent const* a_colliders[2], CollisionData& a_data)
{
    Math::Vector3 sPos = (a_physics[0]->m_transform.GetPosition() + a_physics[0]->m_movement) + a_colliders[0]->m_colliderOffset;
    Math::Vector3 oPos = (a_physics[1]->m_transform.GetPosition() + a_physics[1]->m_movement) + a_colliders[1]->m_colliderOffset;

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

bool Me::Physics::Collision::AABB_Box3DToBox3D(PhysicsComponent const* a_physics[2], BoxCollider3DComponent const* a_colliders[2], CollisionData& a_data)
{
    Math::Vector3 sPos = (a_physics[0]->m_transform.GetPosition() + a_physics[0]->m_movement) + a_colliders[0]->m_colliderOffset;
    Math::Vector3 sHalfSize = a_colliders[0]->m_colliderSize / 2;

    Math::Vector3 oPos = (a_physics[1]->m_transform.GetPosition() + a_physics[1]->m_movement) + a_colliders[1]->m_colliderOffset;
    Math::Vector3 oHalfSize = a_colliders[1]->m_colliderSize / 2;

    if ((sPos.m_x - sHalfSize.m_x <= oPos.m_x + oHalfSize.m_x
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
        a_data.m_hitPoint = Math::Vector3(x, y, z);
        a_data.m_hitNormal = (sPos - a_data.m_hitPoint).Normalize();

        return true;
    }

    return false;
}

bool Me::Physics::Collision::AABB_Box3DToSphere(PhysicsComponent const* a_physics[2], BoxCollider3DComponent const* a_boxColl, SphereColliderComponent const* a_sphereColl, CollisionData& a_data)
{
    Math::Vector3 sPos = (a_physics[0]->m_transform.GetPosition() + a_physics[0]->m_movement) + a_boxColl->m_colliderOffset;
    Math::Vector3 sHalfSize = a_boxColl->m_colliderSize / 2;

    Math::Vector3 spherePos = (a_physics[1]->m_transform.GetPosition() + a_physics[1]->m_movement) + a_sphereColl->m_colliderOffset;

    float x = std::max(sPos.m_x - sHalfSize.m_x, std::min(spherePos.m_x, sPos.m_x + sHalfSize.m_x));
    float y = std::max(sPos.m_y - sHalfSize.m_y, std::min(spherePos.m_y, sPos.m_y + sHalfSize.m_y));
    float z = std::max(sPos.m_z - sHalfSize.m_z, std::min(spherePos.m_z, sPos.m_z + sHalfSize.m_z));

    a_data.m_hitPoint = Math::Vector3(x, y, z);
    float distance = Math::Distance(a_data.m_hitPoint, spherePos);

    bool col = distance <= a_sphereColl->m_radius;

    if (col)
    {
        a_data.m_otherPosition = spherePos;
        a_data.m_hitNormal = (sPos - a_data.m_hitPoint).Normalize();
    }
    return col;
}

bool Me::Physics::Collision::AABB_SphereToBox3D(PhysicsComponent const* a_physics[2], SphereColliderComponent const* a_sphereColl, BoxCollider3DComponent const* a_boxColl, CollisionData& a_data)
{
    Math::Vector3 oPos = (a_physics[1]->m_transform.GetPosition() + a_physics[1]->m_movement) + a_boxColl->m_colliderOffset;
    Math::Vector3 sHalfSize = a_boxColl->m_colliderSize / 2;

    Math::Vector3 spherePos = (a_physics[0]->m_transform.GetPosition() + a_physics[0]->m_movement) + a_sphereColl->m_colliderOffset;

    float x = std::max(oPos.m_x - sHalfSize.m_x, std::min(spherePos.m_x, oPos.m_x + sHalfSize.m_x));
    float y = std::max(oPos.m_y - sHalfSize.m_y, std::min(spherePos.m_y, oPos.m_y + sHalfSize.m_y));
    float z = std::max(oPos.m_z - sHalfSize.m_z, std::min(spherePos.m_z, oPos.m_z + sHalfSize.m_z));

    a_data.m_hitPoint = Math::Vector3(x, y, z);
    float distance = Math::Distance(a_data.m_hitPoint, spherePos);

    bool col = distance <= a_sphereColl->m_radius;

    if (col)
    {
        a_data.m_otherPosition = oPos;
        a_data.m_hitNormal = (spherePos - a_data.m_hitPoint).Normalize();
    }

    return col;
}

bool Me::Physics::Collision::SphereToSphere(PhysicsComponent const* a_physics[2], SphereColliderComponent const* a_sphereCollider[2], CollisionData& a_data)
{
    Math::Vector3 sPos = (a_physics[0]->m_transform.GetPosition() + a_physics[0]->m_movement) + a_sphereCollider[0]->m_colliderOffset;
    Math::Vector3 oPos = (a_physics[1]->m_transform.GetPosition() + a_physics[1]->m_movement) + a_sphereCollider[1]->m_colliderOffset;

    float distance = Math::Distance(sPos, oPos);
    float rad = (a_sphereCollider[0]->m_radius) + (a_sphereCollider[1]->m_radius);

    bool col = distance <= rad;

    if (col)
    {
        a_data.m_otherPosition = oPos;
        a_data.m_hitNormal = (sPos - oPos).Normalize();
    }

    return col;
}
