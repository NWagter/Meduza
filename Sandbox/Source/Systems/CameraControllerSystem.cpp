#include "PCH.h"
#include "Systems/CameraControllerSystem.h"

#include "MeduzaIncluder.h"

CameraControllerSystem::CameraControllerSystem()
{

}

void CameraControllerSystem::OnCreate()
{

}

void CameraControllerSystem::OnUpdate(float a_dt)
{
    

    for(auto& compTuple : m_components)
    {    
        Me::TransformComponent* trans = std::get<Me::TransformComponent*>(compTuple);


        Me::Math::Vec3 moveDir;

        if(Me::Event::EventSystem::GetEventSystem()->KeyDown(Me::Event::KeyCode::W))
        {
            moveDir.m_z++;
        }  
        else if(Me::Event::EventSystem::GetEventSystem()->KeyDown(Me::Event::KeyCode::S))
        {            
            moveDir.m_z--;
        }

        if(Me::Event::EventSystem::GetEventSystem()->KeyDown(Me::Event::KeyCode::D))
        {
            moveDir.m_x++;
        }
        else if(Me::Event::EventSystem::GetEventSystem()->KeyDown(Me::Event::KeyCode::A))
        {
            moveDir.m_x--;
        }


        if(Me::Event::EventSystem::GetEventSystem()->KeyDown(Me::Event::KeyCode::Q))
        {
            trans->m_rotation.m_y += (10) * a_dt;
        }
        else if(Me::Event::EventSystem::GetEventSystem()->KeyDown(Me::Event::KeyCode::E))
        {
            trans->m_rotation.m_y -= (10) * a_dt;
        }

        trans->m_position += (moveDir * 50) * a_dt;

    }
}