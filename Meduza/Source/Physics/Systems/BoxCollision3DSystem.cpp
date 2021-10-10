#include "MePCH.h"
#include "Physics/Systems/BoxCollision3DSystem.h"

#include "Physics/Components/PhysicsComponent.h"
#include "Physics/Components/BoxCollider3DComponent.h"

#include "Physics/Physics.h"
#include "Physics/Collision.h"

Me::Physics::BoxCollision3DSystem::BoxCollision3DSystem()
{

}

void Me::Physics::BoxCollision3DSystem::OnUpdate(float a_dt)
{
    EntityFilter filter;
    filter.insert(PhysicsComponent::s_componentID);
    filter.insert(BoxCollider3DComponent::s_componentID);

    auto entities = EntityManager::GetEntityManager()->GetEntities(filter);
    auto physicsObjects = EntityManager::GetEntityManager()->GetComponents<PhysicsComponent>();
    auto box2DComponents = EntityManager::GetEntityManager()->GetComponents<BoxCollider3DComponent>();
    
    for(auto& compTuple : m_components)
    {
        PhysicsComponent* pC = std::get<PhysicsComponent*>(compTuple);
        BoxCollider3DComponent* bC = std::get<BoxCollider3DComponent*>(compTuple);

        for(auto e : entities)
        {
            if(pC == physicsObjects[e])
                continue;

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

            if(Collision::AABB_CheckCollision(listPhysics, listBox2D, components, data))
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