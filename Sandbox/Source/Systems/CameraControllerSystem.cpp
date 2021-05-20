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


        float forwardMovment = 0;
        float rightMovment = 0 ;
        float upMovment = 0;


        if(Me::Event::EventSystem::GetEventSystem()->KeyDown(Me::Event::KeyCode::Enter))
        {
            Me::Event::EventSystem::GetEventSystem()->ShowCursor(true);
        }

        if(Me::Event::EventSystem::GetEventSystem()->KeyDown(Me::Event::KeyCode::W))
        {
            forwardMovment++;
        }  
        else if(Me::Event::EventSystem::GetEventSystem()->KeyDown(Me::Event::KeyCode::S))
        {            
            forwardMovment--;
        }

        if(Me::Event::EventSystem::GetEventSystem()->KeyDown(Me::Event::KeyCode::D))
        {
            rightMovment++;
        }
        else if(Me::Event::EventSystem::GetEventSystem()->KeyDown(Me::Event::KeyCode::A))
        {
            rightMovment--;
        }

        if(Me::Event::EventSystem::GetEventSystem()->KeyDown(Me::Event::KeyCode::Space))
        {
            upMovment++;
        }
        else if(Me::Event::EventSystem::GetEventSystem()->KeyDown(Me::Event::KeyCode::Shift))
        {
            upMovment--;
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


        Me::Math::Vec3 forward = trans->GetForward() * (forwardMovment * 150);
        Me::Math::Vec3 right = trans->GetRight() * (rightMovment * 150);
        Me::Math::Vec3 up = trans->GetUp() * (upMovment * 150);
        Me::Math::Vec3 movement = forward + right + up;

        trans->Translate(movement * a_dt);
        trans->SetRotationRadian(rotation);
    }
}