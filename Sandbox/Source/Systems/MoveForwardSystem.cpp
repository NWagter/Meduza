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
         
        if(trans->m_isStatic)
            return;

        ForwardComponent* forward = std::get<ForwardComponent*>(compTuple);  

        Me::Math::Vec3 pos = trans->m_translation;
        Me::Math::Mat4 transform = Me::Math::Mat4().Rotation(trans->m_rotation);
        pos += transform.GetForward() * forward->m_forwardSpeed * a_dt;

        trans->m_translation = pos;
    }
}