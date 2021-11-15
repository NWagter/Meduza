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

        Math::Vec3 movementDir = pC->m_movement;
        movementDir.Normalize();
        Math::Vec3 vel = pC->m_velocity;
        vel.Normalize();

        for (const CollisionData& data : pC->m_collided)
        {
            // Velocity Collision
            Math::Vec3 result = vel + data.m_hitNormal;

            Math::Vec3 newVel = pC->m_velocity * (result * result);

            if (!newVel.IsNan())
            {
                pC->m_velocity = newVel;
            }

            if (movementDir.m_x + data.m_hitNormal.m_x == 0)
            {
                pC->m_movement.m_x = 0;
            }

            if (movementDir.m_y + data.m_hitNormal.m_y == 0)
            {
                pC->m_movement.m_y = 0;
            }

            if (movementDir.m_z + data.m_hitNormal.m_z == 0)
            {
                pC->m_movement.m_z = 0;
            }
        } 
    }
}