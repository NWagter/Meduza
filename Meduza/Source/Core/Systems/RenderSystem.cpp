#include "MePCH.h"
#include "Core/Systems/RenderSystem.h"

#include "ECS/Entity.h"
#include "ECS/EntityManager.h"

Me::RenderSystem::RenderSystem()
{
    EntityManager::AddSystem(this);
}

void Me::RenderSystem::Update(float)
{
    auto e = EntityManager::GetEntityManager()->GetEntities(m_filter);

    int counter = 0;
    for(auto ent : e)
    {
        ME_CORE_LOG("Entities! %i \n", counter);
        counter++;
    }
}