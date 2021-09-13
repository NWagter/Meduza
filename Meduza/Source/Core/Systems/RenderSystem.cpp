#include "MePCH.h"
#include "Core/Systems/RenderSystem.h"

#include "ECS/EntityManager.h"

#include "Platform/General/Graphics/RenderLayer.h"

#include "Core/Components/RenderComponent.h"
#include "Core/Components/TransformComponent.h"

Me::RenderSystem::RenderSystem(Renderer::RenderLayer* a_renderLayer)
{ 
    m_renderLayer = a_renderLayer;
    m_executeMask = EXECUTE_ALL;
}

void Me::RenderSystem::OnUpdate(float)
{
    for(auto& compTuple : m_components)
    {
        RenderComponent* rC = std::get<RenderComponent*>(compTuple);
        TransformComponent* tC = std::get<TransformComponent*>(compTuple);
        m_renderLayer->Submit(*rC, *tC);
    }
}