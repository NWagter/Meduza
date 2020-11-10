#include "MePCH.h"
#include "Core/Systems/RenderSystem.h"

#include "ECS/EntityManager.h"

#include "Platform/General/Graphics/RenderLayer.h"

#include "Core/Components/RenderComponent.h"
#include "Core/Components/TransformComponent.h"

Me::RenderSystem::RenderSystem(Renderer::RenderLayer* a_renderLayer)
{ 
    SetFilter();
    m_renderLayer = a_renderLayer;
}

void Me::RenderSystem::SetFilter()
{    
    m_filter.insert(RenderComponent::s_componentID);
    m_filter.insert(TransformComponent::s_componentID);
}

void Me::RenderSystem::Update(float)
{
    // TODO : Improve Component Fetching Dirty Flag it for now in the Container

    auto rContainer = EntityManager::GetComponents<RenderComponent>();
    
    if(!rContainer.empty())
    {
        for(auto r : rContainer)
        {
            m_components.push_back(r.second);
        }
    }

    for(auto c : m_components)
    {
        //m_renderLayer->Submit(*c);
    }
}