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
         
        if(trans->m_isStatic)
            return;

        RotateComponent* rot = std::get<RotateComponent*>(compTuple);  

        Me::Math::Vec3 rotation = trans->m_rotation;

        rotation.m_y += rot->m_rotateSpeed * a_dt;

        trans->m_rotation  = rotation;
    }
}