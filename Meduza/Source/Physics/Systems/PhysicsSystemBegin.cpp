#include "MePCH.h"
#include "Physics/Systems/PhysicsSystemBegin.h"

#include "Physics/Components/PhysicsComponent.h"
#include "Core/Components/TransformComponent.h"

#include "Physics/Physics.h"

Me::Physics::PhysicsSystemBegin::PhysicsSystemBegin()
{ 
    m_executeMask = EXECUTE_INGAME;
}

void Me::Physics::PhysicsSystemBegin::OnUpdate(float a_dt)
{
    ME_PROFILE_FUNC("PhysicsSystem");
    
    for(auto& compTuple : m_components)
    {
        PhysicsComponent* pC = std::get<PhysicsComponent*>(compTuple);
        TransformComponent* tC = std::get<TransformComponent*>(compTuple);

        pC->m_collided.clear();
        pC->m_triggered.clear();

        pC->m_movement = 0;
        pC->m_transform = tC->GetTransform();
    }
}