#include "MePCH.h"
#include "Core/Systems/CameraSystem.h"

#include "ECS/EntityManager.h"

#include "Platform/General/Graphics/RenderLayer.h"

#include "Core/Components/CameraComponent.h"
#include "Core/Components/TransformComponent.h"

#include "Core/Meduza.h"

Me::CameraSystem::CameraSystem(Renderer::RenderLayer* a_renderLayer)
{
    m_renderLayer = a_renderLayer;
    m_executeMask = EXECUTE_ALL;
}

void Me::CameraSystem::OnUpdate(float a_dt)
{
    EntityManager* eManager = EntityManager::GetEntityManager();

    for(int i = 0; i < m_entities.size(); i++)
    {
        if(Meduza::GetEngineState() & RUN_GAME)
        {
            if(eManager->GetComponent<EditorComponent>(m_entities[i]) != nullptr)
            {
                continue;
            }
        }
        else if(Meduza::GetEngineState() & RUN_EDITOR)
        {
            if(eManager->GetComponent<EditorComponent>(m_entities[i]) == nullptr)
            {
                continue;
            }
        }

        CameraComponent* cC = std::get<CameraComponent*>(m_components[i]);
        TransformComponent* tC = std::get<TransformComponent*>(m_components[i]);
        
        m_renderLayer->SetCamera(*cC, *tC);
    }
}