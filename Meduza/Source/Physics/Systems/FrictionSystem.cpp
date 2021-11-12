#include "MePCH.h"
#include "Physics/Systems/FrictionSystem.h"

#include "Physics/Components/PhysicsComponent.h"
#include "Core/Components/TransformComponent.h"

#include "Physics/Physics.h"

Me::Physics::FrictionSystem::FrictionSystem()
{
}

void Me::Physics::FrictionSystem::OnUpdate(float a_dt)
{
    ME_PROFILE_FUNC("FrictionSystem");

    for (auto& compTuple : m_components)
    {
        PhysicsComponent* pC = std::get<PhysicsComponent*>(compTuple);

        //Check if Colliding with Object

    }
}
