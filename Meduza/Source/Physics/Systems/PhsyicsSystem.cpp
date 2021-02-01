#include "MePCH.h"
#include "Physics/Systems/PhysicsSystem.h"

#include "Core/Components/PhysicsComponent.h"
#include "Core/Components/TransformComponent.h"

#include "Physics/Collision.h"

Me::Physics::PhysicsSystem::PhysicsSystem()
{ 

}

void Me::Physics::PhysicsSystem::OnUpdate(float)
{

    auto physicsObjects = EntityManager::GetEntityManager()->GetComponents<PhysicsComponent>();

    for(auto& compTuple : m_components)
    {
        PhysicsComponent* pC = std::get<PhysicsComponent*>(compTuple);
        TransformComponent* tC = std::get<TransformComponent*>(compTuple);

        //Clear Collision Data at start and fill in the collision loop
        pC->m_collisionData.clear();

        Math::Vec3 newPos = tC->m_position;
        Math::Vec3 newRot = tC->m_rotation;
        
        for(auto ph : physicsObjects)
        {
            auto physicsComponent = ph.second;

            CollisionData data;

            if(Collision::CheckCollision(pC->m_body, physicsComponent->m_body, data))
            {
                //Add collisionData

                //Move Object away
            }

        }


        pC->m_body->m_position = tC->m_position = newPos;
        pC->m_body->m_rotation = tC->m_rotation = newRot;
    }
}