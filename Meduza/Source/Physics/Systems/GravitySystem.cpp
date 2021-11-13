#include "MePCH.h"
#include "Physics/Systems/GravitySystem.h"

#include "Physics/Components/PhysicsComponent.h"
#include "Core/Components/TransformComponent.h"

#include "Physics/Physics.h"
#include "Physics/Collision.h"

Me::Physics::GravitySystem::GravitySystem()
{

}

void Me::Physics::GravitySystem::OnUpdate(float a_dt)
{
    ME_PROFILE_FUNC("GravitySystem");
    
    for(auto& compTuple : m_components)
    {
        PhysicsComponent* pC = std::get<PhysicsComponent*>(compTuple);

        if(pC->m_gravity)
        {
            pC->m_velocity.m_y -= ((pC->m_bodyMass * gs_gravity) * a_dt);
        }

    }
}