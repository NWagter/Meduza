#include "PCH.h"
#include "Systems/MoveSystem.h"

#include "MeduzaIncluder.h"

#include "Components/MoveComponent.h"

MoveSystem::MoveSystem()
{

}

void MoveSystem::OnUpdate(float a_time)
{
    for(auto& compTuple : m_components)
    {
        Me::TransformComponent* tC = std::get<Me::TransformComponent*>(compTuple);
        MoveComponent* mC = std::get<MoveComponent*>(compTuple);

        if(mC->m_moveRight)
        {
            tC->m_position.m_x += 64 * a_time;
        }else
        {
            tC->m_position.m_x -= 64 * a_time;
        }

        if(tC->m_position.m_x > 32 * 7)
        {
            mC->m_moveRight = !mC->m_moveRight;
        }else if(tC->m_position.m_x < 0)
        {
            mC->m_moveRight = !mC->m_moveRight;
        }
    }
}