#include "MePCH.h"
#include "Core/Systems/EditorCameraSystem.h"

#include "Core/Components/TransformComponent.h"
#include "Core/Components/CameraComponent.h"

#include "Platform/General/Events/EventSystem.h"

Me::Editor::EditorCameraSystem::EditorCameraSystem()
{
    m_executeMask = EXECUTE_INEDITOR;
}

Me::Editor::EditorCameraSystem::~EditorCameraSystem()
{
    
}

void Me::Editor::EditorCameraSystem::OnCreate()
{
    ME_PROFILE_FUNC("EditorCamera");

    auto eManager = EntityManager::GetEntityManager();

    EntityID editorCam = eManager->CreateEntity("Editor Camera");

    auto cComp = new CameraComponent();
    cComp->m_cameraType = CameraType::Perspective;
    cComp->m_size = Event::EventSystem::GetEventSystem()->ScreenSize();


    auto tComp = new TransformComponent();
    if (cComp->m_cameraType == CameraType::Perspective)
    {
        tComp->m_translation.m_z = -10;
    }

    eManager->AddComponent<EditorComponent>(editorCam);
    eManager->AddComponent(editorCam, tComp);
    eManager->AddComponent(editorCam, cComp);
}

void Me::Editor::EditorCameraSystem::OnUpdate(float a_dt)
{
    if (!Me::Event::EventSystem::GetEventSystem()->IsViewportFocussed())
    {
        return;
    }

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

        Me::Math::Vector3 rotation = trans->m_rotation;

        if(Me::Event::EventSystem::GetEventSystem()->KeyDown(Me::Event::KeyCode::Q))
        {
            rotation.m_yaw += (20.0f) * a_dt;
        }
        else if(Me::Event::EventSystem::GetEventSystem()->KeyDown(Me::Event::KeyCode::E))
        {
            rotation.m_yaw -= (20.0f) * a_dt;
        }
        
        Me::Math::Vector3 position = trans->m_translation;


        Me::Math::Matrix4 transform = Me::Math::Matrix4().Rotation(trans->m_rotation);

        Me::Math::Vector3 forward = transform.GetForward() * (forwardMovment * 10);
        Me::Math::Vector3 right = transform.GetRight() * (rightMovment * 10);
        Me::Math::Vector3 up = transform.GetUp() * (upMovment * 10);
        Me::Math::Vector3 movement = forward + right + up;

        trans->m_translation = trans->m_translation + (movement * a_dt);
        trans->m_rotation = rotation;
    }
}