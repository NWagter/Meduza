#include "MePCH.h"
#include "Core/Systems/RenderSystem.h"

#include "ECS/EntityManager.h"

#include "Platform/General/Graphics/RenderLayer.h"

#include "Core/Components/RenderComponent.h"
#include "Core/Components/TransformComponent.h"

Me::RenderSystem::RenderSystem(Renderer::RenderLayer* a_renderLayer)
{ 
    m_renderLayer = a_renderLayer;
}

void Me::RenderSystem::Update(float)
{
    for(auto& compTuple : m_components)
    {
        RenderComponent* r = std::get<RenderComponent*>(compTuple);
        m_renderLayer->Submit(*r);
    }
}