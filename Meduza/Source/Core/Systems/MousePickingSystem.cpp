#include "MePCH.h"
#include "Core/Systems/MousePickingSystem.h"

#include "Core/Components/TransformComponent.h"
#include "Core/Components/CameraComponent.h"

#include "Platform/General/Events/EventSystem.h"

Me::MousePickingSystem::MousePickingSystem()
{

}

void Me::MousePickingSystem::OnUpdate(float a_dt)
{
    int lowestLayer = -1;
    Event::EventSystem* eventSystem = Event::EventSystem::GetEventSystem();

    CameraComponent* camera = nullptr;
    TransformComponent* transform = nullptr;

    for(auto& compTuple : m_components)
    {
        CameraComponent* cC = std::get<CameraComponent*>(compTuple);
        TransformComponent* tC = std::get<TransformComponent*>(compTuple);

        if(cC->m_cameralayer < lowestLayer || lowestLayer == -1)
        {
            lowestLayer = cC->m_cameralayer;

            camera = cC;
            transform = tC;
        }
    }

    if(camera != nullptr && transform != nullptr)
    {
        eventSystem->SetMouseWorldSpace(*camera, *transform);
    }
}