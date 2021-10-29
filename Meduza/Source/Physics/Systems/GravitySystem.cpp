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
    for(auto& compTuple : m_components)
    {
        PhysicsComponent* pC = std::get<PhysicsComponent*>(compTuple);
        
        bool applyGravity = true;

        for(auto blockData : pC->m_collided)
        {
            if(std::abs(blockData.m_hitNormal.m_y) > 0.01f)
            {
                float gravity = pC->m_gravityForce;

                if(gravity < 0 && (blockData.m_hitNormal.m_y < 0))
                {
                    applyGravity = false;
                }
                else if(gravity > 0 && (blockData.m_hitNormal.m_y > 0)) // gravity check
                {
                    applyGravity = false;
                }
            }
        }

        float yVel = 0;

        if(pC->m_gravity && applyGravity)
        {
            yVel -= ((pC->m_bodyMass * pC->m_gravityForce) * a_dt);
        }
        else
        {
            pC->m_velocity.m_y = 0;
        }

        pC->m_velocity += Math::Vec3(0, yVel, 0);
    }
}