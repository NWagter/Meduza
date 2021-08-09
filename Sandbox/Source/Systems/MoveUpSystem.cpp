#include "PCH.h"
#include "Systems/MoveUpSystem.h"

#include "MeduzaIncluder.h"

MoveUpSystem::MoveUpSystem()
{

}

void MoveUpSystem::OnCreate()
{

}

void MoveUpSystem::OnUpdate(float a_dt)
{
    for(auto& compTuple : m_components)
    {      
        Me::TransformComponent* trans = std::get<Me::TransformComponent*>(compTuple);  
        UpComponent* up = std::get<UpComponent*>(compTuple);  

        Me::Math::Vec3 pos = trans->GetPosition();

        pos += trans->GetUp() * up->m_upSpeed * a_dt;

        trans->SetPosition(pos);
    }
}