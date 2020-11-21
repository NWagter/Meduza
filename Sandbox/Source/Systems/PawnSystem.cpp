#include "PCH.h"
#include "Systems/PawnSystem.h"
#include "Components/TileComponent.h"

#include "MeduzaIncluder.h"

PawnSystem::PawnSystem()
{

}

void PawnSystem::OnUpdate(float a_time)
{
    int eCounter = 0;
    for(auto& compTuple : m_components)
    {
        PawnComponent* pC = std::get<PawnComponent*>(compTuple);
        if(!pC->m_alive)
        {
            //Destroy
            EntityID entt = m_entities.at(eCounter);
            Me::EntityManager::DestroyEntity(entt);
            pC->m_alive = true;
        }

        Me::TransformComponent* tC = std::get<Me::TransformComponent*>(compTuple);
        
        if(pC->m_moving && pC->m_newPos != Me::Math::Vec3())
        {
            tC->m_position = Me::Math::MoveTowards(tC->m_position, pC->m_newPos, pC->m_moveSpeed * a_time);
        }

        if(pC->m_moving && tC->m_position.Distance(pC->m_newPos) < 1.5f)
        {
            auto tile = pC->m_tile; 
            if(tile->m_pawn != nullptr)
            {
                tile->m_pawn->m_alive = false;
            }
            tile->m_pawn = pC;
            tC->m_position = pC->m_newPos;
            pC->m_moving = false;
        }

        eCounter++;
    }
}