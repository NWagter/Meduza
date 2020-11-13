#include "MePCH.h"
#include "ECS/EntityManager.h"

#include "ECS/BaseSystem.h"
#include "ECS/BaseComponent.h"


static EntityID m_entityId = 0;

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
    m_entities.clear();
}

void Me::EntityManager::Update(float a_dt)
{
    for(auto s : m_systems)
    {
        s->Update(a_dt);
    }
}

std::vector<EntityID> Me::EntityManager::GetEntities(EntityFilter a_filter)
{
    // TODO : Filter out entities that contain all the Componets from filter
    std::vector<EntityID> entities;

    for(auto e : m_entities)
    {
        int amount = a_filter.size();

        if(amount <= 0)
        {            
            entities.push_back(e.first);
            continue;
        }

        for(auto eC : e.second)
        {
            for(auto c : a_filter)
            {
                if(eC == c)
                {
                    amount--;
                    break;
                }
            }
            
            if(amount <= 0)
            {
                entities.push_back(e.first);
                break;
            }
        }
    }
   
    return entities;
}

void Me::EntityManager::AddSystem(ECSSystem* a_system)
{
    ms_entityManager->m_systems.push_back(a_system);

    for (auto ent : ms_entityManager->m_entities)
    {
        ms_entityManager->RegisterEntity(ent.first);
    }
    
}

EntityID Me::EntityManager::CreateEntity()
{
    m_entityId++;
    ms_entityManager->m_entities.insert(std::pair<EntityID, std::set<ComponentID>>(m_entityId,{}));
    return m_entityId;
}

void Me::EntityManager::RegisterEntity(EntityID a_entID)
{
	auto ent = m_entities.find(a_entID);
	std::set<ComponentID> eComp = ent->second;

	for (auto s : m_systems)
	{
        s->OnEntityCreated(a_entID);
	}
}