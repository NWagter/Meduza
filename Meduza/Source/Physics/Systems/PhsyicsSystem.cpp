#include "MePCH.h"
#include "Physics/Systems/PhysicsSystem.h"

#include "Core/Components/PhysicsComponent.h"
#include "Core/Components/TransformComponent.h"

#include "Physics/Physics.h"
#include "Physics/Collision.h"

Me::Physics::PhysicsSystem::PhysicsSystem()
{ 
    m_executeMask = EXECUTE_INGAME;
}

void Me::Physics::PhysicsSystem::OnUpdate(float a_dT)
{

    auto physicsObjects = EntityManager::GetEntityManager()->GetComponents<PhysicsComponent>();

    for(auto& compTuple : m_components)
    {
        PhysicsComponent* pC = std::get<PhysicsComponent*>(compTuple);
        TransformComponent* tC = std::get<TransformComponent*>(compTuple);

        //Clear Collision Data at start and fill in the collision loop
        pC->m_collided.clear();
        pC->m_triggered.clear();

        Math::Vec3 newPos = tC->m_translation;
        Math::Vec3 newRot = tC->m_rotation;
        bool applyGravity = true;

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
                data.m_physicsLayerId = physicsComponent->m_physicsLayerId;

                //Add collisionData
                if(pC->m_collisionType == CollisionType::Block)
                {
                    pC->m_collided.push_back(data);

                    //Block Movement
                    if(std::abs(data.m_hitNormal.m_y) > 0.01f)
                    {
                        if(data.m_hitNormal.m_y > 0.01f) // ground check
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
            newPos.m_y -= ((pC->m_body->m_bodyMass * gs_Gravity) * a_dT);
        }

        pC->m_body->m_position = tC->m_translation = newPos;
        pC->m_body->m_rotation = tC->m_rotation = newRot;
    }
}