#pragma once

#include "ECS/EntityTypes.h"

namespace Me
{
    class EntityManager;

    class IComponentContainer
    {
    public:
        IComponentContainer() {}
        virtual ~IComponentContainer() = default;


        virtual bool RemoveComponent(EntityID a_entId) = 0;
        bool m_dirtyFlag = false;
    };

    template<class C>
    class ComponentContainer : IComponentContainer
    {
        public:
        ComponentContainer() {}
        ~ComponentContainer() override {}

        private:
        bool AddComponent(EntityID a_entId, C* a_component);
        bool RemoveComponent(EntityID a_entId);

        C* GetComponent(EntityID a_entId);
		std::map<EntityID, C*> GetComponents();

        std::map<EntityID, C*> m_components;

    friend EntityManager;
    };
    
	template <class C>
	bool ComponentContainer<C>::AddComponent(EntityID a_entId, C* a_component)
	{
        m_dirtyFlag = true;
		auto comp = m_components.find(a_entId);

        if(comp == m_components.end())
        {
            m_components.insert(std::make_pair(a_entId, a_component));
            return true;
        }

        ME_CORE_LOG("Entity already has this Component! \n");

        return false;
	}

    
	template <class C>
	bool ComponentContainer<C>::RemoveComponent(const EntityID a_entId)
	{
        m_dirtyFlag = true;
		auto comp = m_components.find(a_entId);

        if(comp == m_components.end())
        {
            ME_CORE_LOG("Entity doesn't have this Component! \n");
            return false;
        }

		m_components.erase(comp);

		return true;
	}

    template <class C>
	C* ComponentContainer<C>::GetComponent(const EntityID a_entId)
	{
		auto comp = m_components.find(a_entId);

        if(comp == m_components.end())
        {
            ME_CORE_LOG("Entity doesn't have this Component! \n");
			return nullptr;
        }

		return comp->second;
	}

    template <class C>
	std::map<EntityID, C*> ComponentContainer<C>::GetComponents()
	{
        m_dirtyFlag = false;
		return m_components;
	}
}