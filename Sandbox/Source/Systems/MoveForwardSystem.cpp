#include "PCH.h"
#include "Systems/MoveForwardSystem.h"

#include "MeduzaIncluder.h"

MoveForwardSystem::MoveForwardSystem()
{

}

void MoveForwardSystem::OnCreate()
{

}

void MoveForwardSystem::OnUpdate(float a_dt)
{
    for(auto& compTuple : m_components)
    {      
        Me::TransformComponent* trans = std::get<Me::TransformComponent*>(compTuple);  
        ForwardComponent* forward = std::get<ForwardComponent*>(compTuple);  

        Me::Math::Vec3 pos = trans->GetPosition();

        pos += trans->GetForward() * forward->m_forwardSpeed * a_dt;

        trans->SetPosition(pos);
    }
}