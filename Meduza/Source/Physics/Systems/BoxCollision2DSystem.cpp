#include "MePCH.h"
#include "Physics/Systems/BoxCollision2DSystem.h"

#include "Physics/Physics.h"
#include "Physics/Collision.h"

#include "Physics/Components/PhysicsComponent.h"
#include "Physics/Components/BoxCollider2DComponent.h"

Me::Physics::BoxCollision2DSystem::BoxCollision2DSystem()
{

}

void Me::Physics::BoxCollision2DSystem::OnUpdate(float a_dt)
{
    EntityFilter filter;
    filter.insert(PhysicsComponent::s_componentID);
    filter.insert(BoxCollider2DComponent::s_componentID);

    auto entities = EntityManager::GetEntityManager()->GetEntities(filter);
    auto physicsObjects = EntityManager::GetEntityManager()->GetComponents<PhysicsComponent>();
    auto box2DComponents = EntityManager::GetEntityManager()->GetComponents<BoxCollider2DComponent>();
    
    for(auto& compTuple : m_components)
    {
        PhysicsComponent* pC = std::get<PhysicsComponent*>(compTuple);
        BoxCollider2DComponent* bC = std::get<BoxCollider2DComponent*>(compTuple);

        for(auto e : entities)
        {
            CollisionData data;
            data.m_entity = e;
            
            PhysicsComponent* listPhysics[2] = 
            {
                pC, physicsObjects[e]
            };

            ColliderComponent* listBox2D[2] = 
            {
                bC, box2DComponents[e]
            };

            ComponentID components[2] =
            {
                bC->s_componentID,
                box2DComponents[e]->s_componentID
            };

            if(Collision::CheckCollision(listPhysics, listBox2D, components, data))
            {
                data.m_collisionLayerID = box2DComponents[e]->m_collisionLayer;

                //Add collisionData
                if(bC->m_collisionType == CollisionType::Block)
                {
                    pC->m_collided.push_back(data);
                }
                else
                {                
                    pC->m_triggered.push_back(data);
                }
            }
        }
    }    
}