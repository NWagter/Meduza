#include "MePCH.h"
#include "Physics/Systems/FrictionSystem.h"

#include "ECS/EntityManager.h"

#include "Physics/Components/PhysicsComponent.h"
#include "Core/Components/TransformComponent.h"

#include "Physics/Physics.h"

Me::Physics::FrictionSystem::FrictionSystem()
{
}

void Me::Physics::FrictionSystem::OnUpdate(float a_dt)
{
    ME_PROFILE_FUNC("FrictionSystem");

    auto eManager = EntityManager::GetEntityManager();

    for (auto& compTuple : m_components)
    {
        PhysicsComponent* pC = std::get<PhysicsComponent*>(compTuple);

        if (pC->m_velocity.Lenght() <= 0)
        {
            continue;
        }

        //Check if Colliding with Object
        for (const CollisionData& data : pC->m_collided)
        {
            float friction = eManager->GetComponent<PhysicsComponent>(data.m_entity)->m_friction;

            Math::Vec3 frictionVec = (pC->m_velocity * friction) * a_dt;

            if (!frictionVec.IsNan())
            {
                pC->m_velocity -= frictionVec;
            }

        }
    }
}
