#include "MePCH.h"
#include "Core/Systems/MousePickingSystem.h"

#include "Core/Components/TransformComponent.h"
#include "Core/Components/CameraComponent.h"

#include "Platform/General/Events/EventSystem.h"

#include "Core/Meduza.h"

Me::MousePickingSystem::MousePickingSystem()
{
    m_executeMask = EXECUTE_ALL;
}

void Me::MousePickingSystem::OnUpdate(float a_dt)
{
    int lowestLayer = -1;
    Event::EventSystem* eventSystem = Event::EventSystem::GetEventSystem();
    EntityManager* eManager = EntityManager::GetEntityManager();

    CameraComponent* camera = nullptr;
    TransformComponent* transform = nullptr;

    for(int i = 0; i < m_entities.size(); i++)
    {
        CameraComponent* cC = std::get<CameraComponent*>(m_components[i]);
        TransformComponent* tC = std::get<TransformComponent*>(m_components[i]);



        if(Meduza::GetEngineState() & RUN_EDITOR && 
            eManager->GetComponent<EditorComponent>(m_entities[i]) != nullptr)
        {
            if(cC->m_cameralayer < lowestLayer || lowestLayer == -1)
            {
                lowestLayer = cC->m_cameralayer;

                camera = cC;
                transform = tC;
            }
        }
        else if(Meduza::GetEngineState() & RUN_GAME && 
            eManager->GetComponent<EditorComponent>(m_entities[i]) == nullptr)
        {
            if(cC->m_cameralayer < lowestLayer || lowestLayer == -1)
            {
                lowestLayer = cC->m_cameralayer;

                camera = cC;
                transform = tC;
            }
        }
    }

    if(camera != nullptr && transform != nullptr)
    {
        eventSystem->SetMouseWorldSpace(*camera, *transform);
    }
}