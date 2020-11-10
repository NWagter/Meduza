#include "MePCH.h"
#include "Core/Systems/CameraSystem.h"

#include "ECS/EntityManager.h"

#include "Platform/General/Graphics/RenderLayer.h"

#include "Core/Components/CameraComponent.h"
#include "Core/Components/TransformComponent.h"

Me::CameraSystem::CameraSystem(Renderer::RenderLayer* a_renderLayer)
{
    SetFilter();
    m_renderLayer = a_renderLayer;
}

void Me::CameraSystem::SetFilter()
{    
    m_filter.insert(CameraComponent::s_componentID);
    m_filter.insert(TransformComponent::s_componentID);
}

void Me::CameraSystem::Update(float)
{
    for(auto ent : m_entities)
    {
        
    }
}