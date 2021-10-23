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

        static bool EntityExists(EntityID);

        static void AddSystem(ECSSystem*);
        static EntityID CreateEntity(std::string = "Empty Entity");
        static void DestroyEntity(EntityID);

        static void CleanGame();
        static int GetGameEntityAmount();

        template<class C = BaseComponent>
        bool AddComponent(const EntityID a_entID);        
        template<class C = BaseComponent>
        bool RemoveComponent(const EntityID a_entID);

        template<class C = BaseComponent>
        bool AddComponent(const EntityID a_entID, C* a_comp);
        template<class C = BaseComponent>
		C* GetComponent(const EntityID a_entID);
        template<class C = BaseComponent>
		std::map<EntityID, C*> GetComponents();

        void DestroyEntities();
        void Update(float);
        
        std::vector<EntityID> GetEntities(EntityFilter);
        std::map<EntityID, std::set<ComponentID>> GetEntities() {return m_entities;}
        std::map<ComponentID, IComponentContainer*> GetContainers() {return m_containers;}
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
    bool EntityManager::AddComponent(const EntityID a_entID)
    {
        auto container = GetComponentContainer<C>();
        if(container == nullptr)
        {
            container = AddComponentContainer<C>();
        }
        auto comp = new C();

        auto ent = m_entities.find(a_entID);
        ent->second.insert(C::s_componentID);
        container->AddComponent(a_entID, comp);
		RegisterEntity(a_entID);

        return true;
    }

    template<class C>
    bool EntityManager::RemoveComponent(const EntityID a_entID)
    {
        auto container = GetComponentContainer<C>();
        if(container == nullptr)
        {
            return false;
        }

        container->RemoveComponent(a_entID);

        auto ent = m_entities.find(a_entID);
        ent->second.erase(C::s_componentID);
        
        UnRegisterEntity(a_entID);
		RegisterEntity(a_entID);

        return true;
    }

    template<class C>
    bool EntityManager::AddComponent(const EntityID a_entID, C* a_comp)
    {
        auto container = GetComponentContainer<C>();
        if(container == nullptr)
        {
            container = AddComponentContainer<C>();
        }

        auto ent = m_entities.find(a_entID);
        ent->second.insert(C::s_componentID);

        container->AddComponent(a_entID, a_comp);

		RegisterEntity(a_entID);

        return true;
    }    
    template<class C>
    C* EntityManager::GetComponent(const EntityID a_entID)
    {
        auto container = GetComponentContainer<C>();
        if(container == nullptr)
        {
            return nullptr;
        }

		return container->GetComponent(a_entID);
    }

    template<class C>
    std::map<EntityID, C*> EntityManager::GetComponents()
    {
        auto container = GetComponentContainer<C>();

        if(container == nullptr)
        {
            return std::map<EntityID, C*>();
        }

		return container->GetComponents();
    }

}