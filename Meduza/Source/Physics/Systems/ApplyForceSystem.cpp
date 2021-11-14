#include "MePCH.h"
#include "Physics/Systems/ApplyForceSystem.h"

#include "Physics/Components/PhysicsComponent.h"
#include "Core/Components/TransformComponent.h"

#include "Physics/Physics.h"

Me::Physics::ApplyForceSystem::ApplyForceSystem()
{
}

void Me::Physics::ApplyForceSystem::OnUpdate(float a_dt)
{
    ME_PROFILE_FUNC("ApplyForceSystem");

    for (auto& compTuple : m_components)
    {
        PhysicsComponent* pC = std::get<PhysicsComponent*>(compTuple);
    }
}
