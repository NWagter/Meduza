#pragma once

#include "ECS/EntityTypes.h"
#include "ECS/ComponentContainer.h"
#include "ECS/BaseComponent.h"

namespace Me
{
    class ECSSystem;

    class EntityManager
    {
        public:

        static EntityManager* CreateEntityManager();
        static void DestroyEntityManager();
        inline static EntityManager* GetEntityManager() {return ms_entityManager;}

        static bool EntityExists(EntityID const a_entityID);

        static void AddSystem(ECSSystem* a_system);
        static EntityID CreateEntity(std::string a_tag = "", uint64_t const a_guid = 0);
        static void DestroyEntity(EntityID const a_entityID);

        static void CleanGame();
        static int GetGameEntityAmount();

        template<class C = BaseComponent>
        bool AddComponent(EntityID const a_entityID);
        template<class C = BaseComponent>
        bool RemoveComponent(EntityID const a_entityID);

        template<class C = BaseComponent>
        bool AddComponent(EntityID const a_entityID, C* a_component);
        template<class C = BaseComponent>
		C* GetComponent(EntityID const a_entityID);
        template<class C = BaseComponent>
		std::map<EntityID, C*> const& GetComponents();

        void DestroyEntities();
        void Update(float a_dt);
        
        std::vector<EntityID> GetEntities(EntityFilter);
        std::map<EntityID, std::set<ComponentID>> const& GetEntities() {return m_entities;}
        std::map<ComponentID, IComponentContainer*> const& GetContainers() {return m_containers;}
        private:
        EntityManager();
        ~EntityManager();
        static EntityManager* ms_entityManager;
        bool m_started = false;

        std::map<EntityID, std::set<ComponentID>> m_entities;        

        std::vector<EntityID> m_entitiesToDestroy;

        std::vector<ECSSystem*> m_systems;
		std::map<ComponentID, IComponentContainer*> m_containers;
        std::map<ComponentID, std::string> m_componentNames;

        template<class C = BaseComponent>
		ComponentContainer<C>* AddComponentContainer();	
        template<class C = BaseComponent>
		void RemoveComponentContainer();
		template<class C = BaseComponent>
		ComponentContainer<C>* GetComponentContainer();

        void RegisterEntity(EntityID);
        void UnRegisterEntity(EntityID);

        friend ECSSystem;
    };
//====== Component Container Logics!
    template<class C>
    ComponentContainer<C>* EntityManager::AddComponentContainer()
    {
        ComponentContainer<C>* container = new ComponentContainer<C>();
        m_containers.insert(std::pair<ComponentID, IComponentContainer*>(C::s_componentID, container));
        return container;
    }
    template<class C>
    void EntityManager::RemoveComponentContainer()
    {
        auto container = std::find(m_containers.begin(), m_containers.end(), C::s_componentID);
		m_containers.erase(container);
    }
    template<class C>
    ComponentContainer<C>* EntityManager::GetComponentContainer()
    {
        if(m_containers.empty())
        {
            return nullptr;
        }

        auto container = m_containers.find(C::s_componentID);
        if(container == m_containers.end())
        {
            return nullptr;
        }

        auto dContainer = static_cast<ComponentContainer<C>*>(container->second);

        return dContainer;
    }

//===== Component Logics

    template<class C>
    bool EntityManager::AddComponent(EntityID const a_entityID)
    {
        auto container = GetComponentContainer<C>();
        if(container == nullptr)
        {
            container = AddComponentContainer<C>();
        }
        auto comp = new C();

        auto ent = m_entities.find(a_entityID);

        if(!ent->second.empty())
        {
            RemoveComponent<C>(a_entityID);
        }

        ent->second.insert(C::s_componentID);
        container->AddComponent(a_entityID, comp);
		RegisterEntity(a_entityID);

        return true;
    }

    template<class C>
    bool EntityManager::RemoveComponent(EntityID const a_entityID)
    {
        auto container = GetComponentContainer<C>();
        if(container == nullptr)
        {
            return false;
        }

        container->RemoveComponent(a_entityID);

        auto ent = m_entities.find(a_entityID);
        ent->second.erase(C::s_componentID);
        
        UnRegisterEntity(a_entityID);
		RegisterEntity(a_entityID);

        return true;
    }

    template<class C>
    bool EntityManager::AddComponent(EntityID const a_entityID, C* a_component)
    {
        auto container = GetComponentContainer<C>();
        if(container == nullptr)
        {
            container = AddComponentContainer<C>();
        }

        auto ent = m_entities.find(a_entityID);

        if(!ent->second.empty())
        {
            RemoveComponent<C>(a_entityID);
        }

        ent->second.insert(C::s_componentID);

        container->AddComponent(a_entityID, a_component);

		RegisterEntity(a_entityID);

        return true;
    }    
    template<class C>
    C* EntityManager::GetComponent(EntityID const a_entityID)
    {
        auto container = GetComponentContainer<C>();
        if(container == nullptr)
        {
            return nullptr;
        }

		return container->GetComponent(a_entityID);
    }

    template<class C>
    std::map<EntityID, C*> const& EntityManager::GetComponents()
    {
        auto container = GetComponentContainer<C>();

        if(container == nullptr)
        {
            return AddComponentContainer<C>()->GetComponents();
        }

		return container->GetComponents();
    }

}