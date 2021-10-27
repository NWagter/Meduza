#include "MePCH.h"
#include "Physics/Systems/PhysicsSystem.h"

#include "Physics/Components/PhysicsComponent.h"
#include "Core/Components/TransformComponent.h"

#include "Physics/Physics.h"
#include "Physics/Collision.h"

Me::Physics::PhysicsSystem::PhysicsSystem()
{ 
    m_executeMask = EXECUTE_INGAME;
}

void Me::Physics::PhysicsSystem::OnUpdate(float a_dT)
{
    for(auto& compTuple : m_components)
    {
        PhysicsComponent* pC = std::get<PhysicsComponent*>(compTuple);
        TransformComponent* tC = std::get<TransformComponent*>(compTuple);

        pC->m_collided.clear();
        pC->m_triggered.clear();

        tC->m_translation += pC->m_velocity * a_dT;

        pC->m_position = tC->m_translation;
        pC->m_rotation = tC->m_rotation;
    }
}