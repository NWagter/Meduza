#include "PCH.h"
#include "Systems/MoveSystem.h"

#include "MeduzaIncluder.h"

#include "Components/MoveComponent.h"

MoveSystem::MoveSystem()
{

}

void MoveSystem::Update(float a_time)
{
    for(auto& compTuple : m_components)
    {
        Me::TransformComponent* tC = std::get<Me::TransformComponent*>(compTuple);
        MoveComponent* mC = std::get<MoveComponent*>(compTuple);

        if(mC->m_moveUp)
        {
            tC->m_position.m_y += 50 * a_time;
        }else
        {
            tC->m_position.m_y -= 50 * a_time;
        }

        if(tC->m_position.m_y < - 250 || tC->m_position.m_y > 250)
        {
            mC->m_moveUp = !mC->m_moveUp;
        }
    }
}