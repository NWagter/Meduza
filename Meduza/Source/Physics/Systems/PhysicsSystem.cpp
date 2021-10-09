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

        pC->m_position = tC->m_translation;
        pC->m_rotation = tC->m_rotation;

        /*
        for(auto ph : physicsObjects)
        {
            auto physicsComponent = ph.second;

            if(physicsComponent == pC)
            {
                continue;
            }

            CollisionData data;
            data.m_entity = ph.first;

            if(Collision::CheckCollision(pC->m_body, physicsComponent->m_body, data))
            {
                data.m_collisionLayerID = physicsComponent->m_collisionLayerID;

                //Add collisionData
                if(pC->m_collisionType == CollisionType::Block)
                {

                    pC->m_collided.push_back(data);

                    //Block Movement
                    if(std::abs(data.m_hitNormal.m_y) > 0.01f)
                    {
                        float gravity = pC->m_body->m_gravityForce;

                        if(gravity < 0 && (data.m_hitNormal.m_y < 0))
                        {
                            applyGravity = false;
                        }
                        else if(gravity > 0 && (data.m_hitNormal.m_y > 0)) // gravity check
                        {
                            applyGravity = false;
                        }
                        
                        newPos.m_y = pC->m_body->m_position.m_y;
                    }
                    if(std::abs(data.m_hitNormal.m_x) > 0.01f)
                    {
                        newPos.m_x = pC->m_body->m_position.m_x;
                    }
                }
                else
                {
                    pC->m_triggered.push_back(data);
                }
            }
        }
        

        if(pC->m_gravity && applyGravity)
        {
            newPos.m_y -= ((pC->m_bodyMass * pC->m_gravityForce) * a_dT);
        }
        */
    }
}