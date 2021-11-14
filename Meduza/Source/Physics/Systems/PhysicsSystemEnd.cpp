#include "MePCH.h"
#include "Physics/Systems/PhysicsSystemEnd.h"

#include "Physics/Components/PhysicsComponent.h"
#include "Core/Components/TransformComponent.h"

#include "Physics/Physics.h"
#include "Physics/Collision.h"

Me::Physics::PhysicsSystemEnd::PhysicsSystemEnd()
{
    m_executeMask = EXECUTE_INGAME;
}

void Me::Physics::PhysicsSystemEnd::OnUpdate(float a_dT)
{
    ME_PROFILE_FUNC("PhysicsSystem");

    for (auto& compTuple : m_components)
    {
        PhysicsComponent* pC = std::get<PhysicsComponent*>(compTuple);
        TransformComponent* tC = std::get<TransformComponent*>(compTuple);

        Math::Vec3 vP = pC->m_velocity * a_dT;

        if (!vP.IsNan())
        {
            pC->m_movement += vP;
        }

        tC->m_translation += pC->m_movement;
    }
}