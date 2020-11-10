#pragma once

#include "ECS/EntityTypes.h"
#include "ECS/ComponentContainer.h"
#include "ECS/BaseComponent.h"

namespace Me
{
    class BaseSystem;

    class EntityManager
    {
        public:

        static EntityManager* CreateEntityManager();
        static void DestroyEntityManager();
        inline static EntityManager* GetEntityManager() {return ms_entityManager;}

        static void AddSystem(BaseSystem*);
        static EntityID CreateEntity();

        template<class C = BaseComponent>
        static bool AddComponent(const EntityID a_entID);
        template<class C = BaseComponent>
        static bool AddComponent(const EntityID a_entID, C* a_comp);
        template<class C = BaseComponent>
		static C* GetComponent(const EntityID a_entID);
        template<class C = BaseComponent>
		static std::map<EntityID, C*> GetComponents();


        void Update(float);
        
        std::vector<EntityID> GetEntities(EntityFilter);

        private:
        EntityManager();
        ~EntityManager();
        static EntityManager* ms_entityManager;

        std::map<EntityID, std::set<ComponentID>> m_entities;
        std::vector<BaseSystem*> m_systems;
		std::map<ComponentID, IComponentContainer*> m_containers;

        template<class C = BaseComponent>
		ComponentContainer<C>* AddComponentContainer();	
        template<class C = BaseComponent>
		void RemoveComponentContainer();
		template<class C = BaseComponent>
		ComponentContainer<C>* GetComponentContainer();

        void RegisterEntity(EntityID);

        friend BaseSystem;
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
        auto container = std::find(m_containers.begin(), m_containers.end(), C::GetComponentID());
		m_containers.erase(container);
    }
    template<class C>
    ComponentContainer<C>* EntityManager::GetComponentContainer()
    {
        if(m_containers.empty())
        {
            ME_CORE_LOG("There are like zero containers what are you even trying to do? MATE \n");
            return nullptr;
        }

        auto container = m_containers.find(C::s_componentID);
        if(container == m_containers.end())
        {
            ME_CORE_LOG("This is not the container you are looking for \n");
            return nullptr;
        }

        auto dContainer = static_cast<ComponentContainer<C>*>(container->second);

        return dContainer;
    }

//===== Component Logics

    template<class C>
    static bool EntityManager::AddComponent(const EntityID a_entID)
    {
        auto container = ms_entityManager->GetComponentContainer<C>();
        if(container == nullptr)
        {
            container = ms_entityManager->AddComponentContainer<C>();
        }
        auto comp = new C();

        auto ent = ms_entityManager->m_entities.find(a_entID);
        ent->second.insert(C::s_componentID);
		ms_entityManager->RegisterEntity(a_entID);

        return container->AddComponent(a_entID, comp);
    }

    template<class C>
    static bool EntityManager::AddComponent(const EntityID a_entID, C* a_comp)
    {
        auto container = ms_entityManager->GetComponentContainer<C>();
        if(container == nullptr)
        {
            container = ms_entityManager->AddComponentContainer<C>();
        }

        auto ent = ms_entityManager->m_entities.find(a_entID);
        ent->second.insert(C::s_componentID);
		ms_entityManager->RegisterEntity(a_entID);

        return container->AddComponent(a_entID, a_comp);
    }    
    template<class C>
    static C* EntityManager::GetComponent(const EntityID a_entID)
    {
        auto container = ms_entityManager->GetComponentContainer<C>();
        if(container == nullptr)
        {
            return nullptr;
        }

		return container->GetComponent(a_entID);
    }

    template<class C>
    static std::map<EntityID, C*> EntityManager::GetComponents()
    {
        auto container = ms_entityManager->GetComponentContainer<C>();
        if(!container->m_dirtyFlag)
        {
            return std::map<EntityID, C*>{};
        }
		return container->GetComponents();
    }

}