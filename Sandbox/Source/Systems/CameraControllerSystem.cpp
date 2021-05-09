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

        Me::Math::Vec3 rotation = trans->GetRotation();

        if(Me::Event::EventSystem::GetEventSystem()->KeyDown(Me::Event::KeyCode::Q))
        {
            rotation.m_yaw += (10) * a_dt;
        }
        else if(Me::Event::EventSystem::GetEventSystem()->KeyDown(Me::Event::KeyCode::E))
        {
            rotation.m_yaw -= (10) * a_dt;
        }

        Me::Math::Vec3 position = trans->GetPosition();
        position += (moveDir * 150) * a_dt;

        trans->SetPosition(position);
        trans->SetRotationRadian(rotation);
    }
}