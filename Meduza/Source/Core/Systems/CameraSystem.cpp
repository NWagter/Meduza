#include "MePCH.h"
#include "Core/Systems/CameraSystem.h"

#include "ECS/EntityManager.h"

#include "Platform/General/Graphics/RenderLayer.h"

#include "Core/Components/CameraComponent.h"
#include "Core/Components/TransformComponent.h"

Me::CameraSystem::CameraSystem(Renderer::RenderLayer* a_renderLayer)
{
    m_renderLayer = a_renderLayer;
}

void Me::CameraSystem::OnUpdate(float a_dt)
{
    for(auto& compTuple : m_components)
    {
        CameraComponent* cC = std::get<CameraComponent*>(compTuple);
        TransformComponent* tC = std::get<TransformComponent*>(compTuple);
        
        m_renderLayer->SetCamera(*cC, *tC);
    }
}