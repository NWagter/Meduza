#include "MePCH.h"
#include "Core/Systems/RenderSystem.h"

#include "ECS/Entity.h"
#include "ECS/EntityManager.h"

#include "Platform/General/Graphics/RenderLayer.h"

#include "Core/Components/RenderComponent.h"

Me::RenderSystem::RenderSystem(Renderer::RenderLayer* a_renderLayer)
{
    EntityManager::AddSystem(this);
    m_renderLayer = a_renderLayer;
}

void Me::RenderSystem::Update(float)
{
    auto e = EntityManager::GetEntityManager()->GetEntities(m_filter);

    int counter = 0;
    for(auto ent : e)
    {
        auto r = static_cast<RenderComponent*>(ent->GetComponent(RenderComponent::m_componentID));
        m_renderLayer->Submit(*r);

        counter++;
    }
}