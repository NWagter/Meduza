#include "PCH.h"
#include "Systems/PawnSystem.h"

#include "MeduzaIncluder.h"

PawnSystem::PawnSystem()
{

}

void PawnSystem::OnUpdate(float a_time)
{
    for(auto& compTuple : m_components)
    {
        Me::TransformComponent* tC = std::get<Me::TransformComponent*>(compTuple);
        PawnComponent* pC = std::get<PawnComponent*>(compTuple);
        
        if(pC->m_moving && pC->m_newPos != Me::Math::Vec3())
        {
            tC->m_position = Me::Math::MoveTowards(tC->m_position, pC->m_newPos, pC->m_moveSpeed * a_time);
        }

        if(pC->m_moving && tC->m_position.Distance(pC->m_newPos) < 1.5f)
        {
            tC->m_position = pC->m_newPos;
            pC->m_moving = false;
        }
    }
}