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

        float xVel = 0;
        float yVel = 0;
        float zVel = 0;

        if(pC->m_gravity && applyGravity)
        {
            yVel -= ((pC->m_bodyMass * pC->m_gravityForce) * a_dt);
        }
        else
        {
            pC->m_velocity.m_y = 0;
        }

        if(pC->m_velocity.m_x < -0.1f)
        {
            xVel += (pC->m_bodyMass * pC->m_friction) * a_dt;
        }
        else if(pC->m_velocity.m_x > 0.1f)
        {
            xVel -= (pC->m_bodyMass * pC->m_friction) * a_dt;
        }
        else
        {
            pC->m_velocity.m_x = 0;
        }

        
        if(pC->m_velocity.m_z < -0.1f)
        {
            zVel += (pC->m_bodyMass * pC->m_friction) * a_dt;
        }
        else if(pC->m_velocity.m_z > 0.1f)
        {
            zVel -= (pC->m_bodyMass * pC->m_friction) * a_dt;
        }
        else
        {
            pC->m_velocity.m_z = 0;
        }

        pC->m_velocity += Math::Vec3(xVel, yVel, zVel);
    }
}