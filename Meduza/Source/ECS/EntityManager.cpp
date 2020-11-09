#include "MePCH.h"
#include "ECS/EntityManager.h"

#include "ECS/Entity.h"
#include "ECS/BaseSystem.h"
#include "ECS/BaseComponent.h"


Me::EntityManager* Me::EntityManager::ms_entityManager = nullptr;

Me::EntityManager* Me::EntityManager::CreateEntityManager()
{
    if(ms_entityManager != nullptr)
    {
        ME_CORE_LOG("Entity Manager already Exitst!");
        return ms_entityManager;
    }

    ms_entityManager = new EntityManager();
    return ms_entityManager;
}

void Me::EntityManager::DestroyEntityManager()
{
    delete ms_entityManager;
    ms_entityManager = nullptr;
}

Me::EntityManager::EntityManager()
{

}

Me::EntityManager::~EntityManager()
{
    for(auto e : m_entities)
    {
        delete e;
    }

    m_entities.clear();
}

void Me::EntityManager::Update(float a_dt)
{
    for(auto s : m_systems)
    {
        s->Update(a_dt);
    }
}

std::vector<Me::Entity*> Me::EntityManager::GetEntities(EntityFilter a_filter)
{
    // TODO : Filter out entities that contain all the Componets from filter
    std::vector<Entity*> entities;

    for(auto e : m_entities)
    {
        size_t components = a_filter.size();

        for (auto cId : a_filter)
        {      
            if(components == 0)
            {
                break;
            }

            if(e->HasComponent(cId))
            {
                components--;
            }
        }
        
 
        if(components == 0)
        {
            entities.push_back(e);
        }
    }

    return entities;
}

void Me::EntityManager::AddSystem(BaseSystem* a_system)
{
    ms_entityManager->m_systems.push_back(a_system);
}

Me::Entity* Me::EntityManager::CreateEntity()
{
    auto e = new Entity();

    ms_entityManager->m_entities.push_back(e);

    return e;
}
bool Me::EntityManager::AddComponent(Entity* a_entity, BaseComponent* a_comp)
{
    return a_entity->AddComponent(a_comp);
}