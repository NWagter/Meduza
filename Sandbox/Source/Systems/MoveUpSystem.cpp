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
         
        if(trans->m_isStatic)
            return;

        UpComponent* up = std::get<UpComponent*>(compTuple);  

        Me::Math::Vec3 pos = trans->m_translation;
        Me::Math::Mat4 transform = Me::Math::Mat4().Rotation(trans->m_rotation);

        pos += transform.GetUp() * up->m_upSpeed * a_dt;

        trans->m_translation = pos;
    }
}