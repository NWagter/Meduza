#include "PCH.h"
#include "Systems/Rotator.h"

#include "MeduzaIncluder.h"

Rotator::Rotator()
{

}

void Rotator::OnCreate()
{

}

void Rotator::OnUpdate(float a_dt)
{
    for(auto& compTuple : m_components)
    {      
        Me::TransformComponent* trans = std::get<Me::TransformComponent*>(compTuple);  
        RotateComponent* rot = std::get<RotateComponent*>(compTuple);  

        trans->m_rotation.m_x += rot->m_rotateSpeed * a_dt;
        trans->m_rotation.m_z += rot->m_rotateSpeed * a_dt;
    }
}