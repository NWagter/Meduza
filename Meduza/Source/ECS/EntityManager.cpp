#include "MePCH.h"
#include "ECS/EntityManager.h"

#include "ECS/BaseSystem.h"
#include "ECS/BaseComponent.h"

#include "Core/Meduza.h"

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
    for(auto e : m_entities)
    {
        DestroyEntity(e.first);
    }
    m_entities.clear();
    
    for(auto cC : m_containers)
    {        
        if(cC.second != nullptr)
        {
            delete cC.second;
        }
    }
    m_containers.clear();
}

bool Me::EntityManager::EntityExists(EntityID a_entity)
{
    auto const& entities = ms_entityManager->m_entities;
    if(entities.size() <= 0)
    {
        return false;
    }

    auto it = entities.find(a_entity);

    if(it == entities.end())
    {
        return false;
    }

    return true;
}

void Me::EntityManager::DestroyEntities()
{
    for(auto entId : m_entitiesToDestroy)
    {
        ms_entityManager->UnRegisterEntity(entId);

        for(auto container : ms_entityManager->m_containers)
        {
            container.second->RemoveComponent(entId);
        }

        ms_entityManager->m_entities.erase(entId);
    }

    m_entitiesToDestroy.clear();
}

void Me::EntityManager::Update(float a_dt)
{
    DestroyEntities();

    for(auto s : m_systems)
    {
        if(!s->m_OnCreated)
        {
            s->OnCreate();
            s->m_OnCreated = true;
        }

        if(Meduza::GetEngineState() & (RUN_GAME | RUN_PAUSED))
        {
            if(!m_started)
            {
                s->OnStart();
            }

            if (s->m_executeMask & (EXECUTE_ALL))
            {
                s->OnUpdate(a_dt);
            }

            if (Meduza::GetEngineState() & (RUN_GAME) && s->m_executeMask & (EXECUTE_INGAME))
            {
                s->OnUpdate(a_dt);
            }
        }
        else if(Meduza::GetEngineState() & RUN_EDITOR)
        {      

            if(s->m_executeMask & (EXECUTE_INEDITOR | EXECUTE_ALL))
            {
                s->OnUpdate(a_dt);
            } 
        }
    }

    if(m_started && Meduza::GetEngineState() & RUN_EDITOR)
    {
        m_started = false;
    }
    else if(!m_started &&Meduza::GetEngineState() & (RUN_GAME | RUN_PAUSED))
    {
        m_started = true;
    }
}

std::vector<EntityID> Me::EntityManager::GetEntities(EntityFilter a_filter)
{
    // TODO : Filter out entities that contain all the Componets from filter
    std::vector<EntityID> entities;

    for(auto const& e : m_entities)
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

EntityID Me::EntityManager::CreateEntity(std::string a_tag)
{
    m_entityId++;
    ms_entityManager->m_entities.insert(std::pair<EntityID, std::set<ComponentID>>(m_entityId,{}));

    if(a_tag != "")
    {
        TagComponent* tag = new TagComponent();
        tag->m_tag = a_tag;
        ms_entityManager->AddComponent(m_entityId, tag);
    }

    return m_entityId;
}

void Me::EntityManager::DestroyEntity(EntityID a_entID)
{
    ms_entityManager->m_entitiesToDestroy.push_back(a_entID);
}

void Me::EntityManager::CleanGame()
{
    auto list = ms_entityManager->m_entities;
    for(auto ent : list)
    {
        if(ms_entityManager->GetComponent<EditorComponent>(ent.first) != nullptr)
        {
            continue;
        }

        ms_entityManager->DestroyEntity(ent.first);
    }
}

int Me::EntityManager::GetGameEntityAmount()
{
    int gameEntities = 0;
    for(auto ent : ms_entityManager->GetEntities())
    {        
        if(ms_entityManager->GetComponent<Me::EditorComponent>(ent.first) != nullptr)
        {
            continue;
        }
        gameEntities++;
    }

    return gameEntities;
}

void Me::EntityManager::RegisterEntity(EntityID a_entID)
{
	for (auto s : m_systems)
	{
        //Check if entity already is included to the system!
        if(std::find(s->m_entities.begin(), s->m_entities.end(),a_entID) != s->m_entities.end())
        {
            continue;
        }
        
        s->OnEntityCreated(a_entID);
	}
}

void Me::EntityManager::UnRegisterEntity(EntityID a_entID)
{
    for (auto s : m_systems)
	{
        //Check if entity already is included to the system!
        if(std::find(s->m_entities.begin(), s->m_entities.end(),a_entID) != s->m_entities.end())
        {
            s->OnEntityDestroy(a_entID);
        }        
	}
}