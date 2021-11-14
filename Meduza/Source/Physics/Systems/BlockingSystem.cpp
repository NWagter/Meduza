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

    for (int i = 0; i < m_entities.size(); i++)
    {
        PhysicsComponent* pC = std::get<PhysicsComponent*>(m_components.at(i));
        TransformComponent* tC = std::get<TransformComponent*>(m_components.at(i));

        if (pC->m_velocity.Lenght() <= 0.1f)
        {
            continue;
        }

        Math::Vec3 movementDir = (pC->m_position - tC->m_translation).Normalize();

        for (const CollisionData& data : pC->m_collided)
        {
            // Translation Collision

            if (movementDir.m_x + data.m_hitNormal.m_x == 0)
            {
                pC->m_position.m_x = tC->m_translation.m_x;
            }
            if (movementDir.m_y + data.m_hitNormal.m_y == 0)
            {
                pC->m_position.m_y = tC->m_translation.m_y;
            }
            if (movementDir.m_z + data.m_hitNormal.m_z == 0)
            {
                pC->m_position.m_z = tC->m_translation.m_z;
            }

            // Velocity Collision

            Math::Vec3 newVel = (pC->m_velocity * data.m_hitNormal).Inverse();

            if (!newVel.IsNan())
            {
                pC->m_velocity += newVel;
            }
        } 
    }
}