#include "PCH.h"
#include "Systems/Physics2D/OverlapSystem.h"

#include "MeduzaIncluder.h"

OverlapSystem::OverlapSystem()
{

}

void OverlapSystem::OnCreate()
{

}

void OverlapSystem::OnUpdate(float a_dt)
{
    for(auto& compTuple : m_components)
    {      
        Me::TransformComponent* tC = std::get<Me::TransformComponent*>(compTuple);  
        Me::Physics::PhysicsComponent* pC = std::get<Me::Physics::PhysicsComponent*>(compTuple);  

        for(auto c : pC->m_triggered)
        {
            if(c.m_physicsLayerId == 1)
            {
                Me::EntityManager::GetEntityManager()->DestroyEntity(c.m_entity);
            }
        }
    }
}