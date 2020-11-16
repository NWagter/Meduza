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

        if(tC->m_position.m_x >= (32 * 7))
        {            
            mC->m_destination = Me::Math::Vec3(0, 0, tC->m_position.m_z);
        }
        else if(tC->m_position.m_x <= 0)
        {            
            mC->m_destination = Me::Math::Vec3(32 * 7, 0, tC->m_position.m_z);
        }

        tC->m_position = Me::Math::MoveTowards(tC->m_position, mC->m_destination, 25.f * a_time);
    }
}