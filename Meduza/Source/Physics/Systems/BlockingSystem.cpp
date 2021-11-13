#include "MePCH.h"
#include "Physics/Systems/BlockingSystem.h"

#include "Physics/Components/PhysicsComponent.h"
#include "Core/Components/TransformComponent.h"

#include "Physics/Physics.h"
#include "Physics/Collision.h"

Me::Physics::BlockingSystem::BlockingSystem()
{
    m_executeMask = EXECUTE_INGAME;
}

void Me::Physics::BlockingSystem::OnUpdate(float a_dT)
{
    ME_PROFILE_FUNC("BlockingSystem");
    auto eManager = EntityManager::GetEntityManager();

    for (auto& compTuple : m_components)
    {
        PhysicsComponent* pC = std::get<PhysicsComponent*>(compTuple);
        TransformComponent* tC = std::get<TransformComponent*>(compTuple);

        if (pC->m_velocity.Lenght() == 0)
        {
            continue;
        }

        for (const CollisionData& data : pC->m_collided)
        {
            Math::Vec3 newVec = pC->m_velocity * data.m_hitNormal;
            pC->m_velocity -= newVec;
        } 
    }
}