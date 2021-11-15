#include "MePCH.h"
#include "Physics/Systems/CollisionSystem.h"

#include "Physics/Physics.h"
#include "Physics/Collision.h"

#include "Physics/Components/PhysicsComponent.h"
#include "Physics/Components/ColliderComponent.h"

#include "Utils/MeduzaDebug.h"

Me::Physics::CollisionSystem::CollisionSystem()
{

}

void Me::Physics::CollisionSystem::OnUpdate(float a_dt)
{
    ME_PROFILE_FUNC("CollisionSystem");
    
    EntityFilter filter;
    filter.insert(PhysicsComponent::s_componentID);
    filter.insert(ColliderTagComponent::s_componentID);

    auto entities = EntityManager::GetEntityManager()->GetEntities(filter);
    auto physicsObjects = EntityManager::GetEntityManager()->GetComponents<PhysicsComponent>();
    auto colliderComponents = EntityManager::GetEntityManager()->GetComponents<ColliderTagComponent>();
    
    for(auto& compTuple : m_components)
    {
        PhysicsComponent* pC = std::get<PhysicsComponent*>(compTuple);
        ColliderTagComponent* bC = std::get<ColliderTagComponent*>(compTuple);
        TagComponent* tC = std::get<TagComponent*>(compTuple);

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
                bC->m_collider, colliderComponents[e]->m_collider
            };

            ComponentID components[2] =
            {
                bC->m_collider->GetColliderComponentID(),
                colliderComponents[e]->m_collider->GetColliderComponentID()
            };

            if(Collision::AABB_CheckCollision(listPhysics, listBox2D, components, data))
            {
                data.m_collisionLayerID = colliderComponents[e]->m_collider->m_collisionLayer;

                //Add collisionData
                if(bC->m_collider->m_collisionType == CollisionType::Block && 
                    colliderComponents[e]->m_collider->m_collisionType != CollisionType::Overlap)
                {
                    pC->m_collided.push_back(data);
                }
                else
                {                
                    pC->m_triggered.push_back(data);
                }


                //Draw Hit Normal
                if (pC->m_debugHitNormals)
                {
                    Debug::MeduzaDebug::RenderLine(data.m_hitPoint, data.m_hitNormal, Debug::MeduzaDebug::GetDebuggingSettings().m_debugLineLenght);
                }
            }
        }
    }    
}