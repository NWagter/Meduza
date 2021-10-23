#pragma once

#include "ECS/EntityTypes.h"

namespace Me
{
    class EntityManager;
    class BaseComponent;

    class IComponentContainer
    {
    public:
        IComponentContainer() {}
        virtual ~IComponentContainer() = default;

        virtual BaseComponent* GetBaseComponent(EntityID a_entId) = 0;
        virtual bool RemoveComponent(EntityID a_entId) = 0;
    };

    template<class C>
    class ComponentContainer : IComponentContainer
    {
        public:
        ComponentContainer() {}
        ~ComponentContainer() override 
        {
            for(auto c : m_components)
            {
                if(c.second != nullptr)
                {
                    delete c.second;
                }
            }
        }

        private:
        bool AddComponent(EntityID a_entId, C* a_component);
        bool RemoveComponent(EntityID a_entId);

        C* GetComponent(EntityID a_entId);

        BaseComponent* GetBaseComponent(const EntityID a_entId) override;
		std::map<EntityID, C*> GetComponents();

        std::map<EntityID, C*> m_components;

    friend EntityManager;
    };
    
	template <class C>
	bool ComponentContainer<C>::AddComponent(EntityID a_entId, C* a_component)
	{
		auto comp = m_components.find(a_entId);

        if(comp == m_components.end())
        {
            m_components.insert(std::make_pair(a_entId, a_component));
            return true;
        }

        return false;
	}

    
	template <class C>
	bool ComponentContainer<C>::RemoveComponent(const EntityID a_entId)
	{
		auto comp = m_components.find(a_entId);

        if(comp == m_components.end())
        {
            return false;
        }

        auto component = m_components.at(a_entId);

		m_components.erase(comp);
        delete component;

		return true;
	}

    template <class C>
	C* ComponentContainer<C>::GetComponent(const EntityID a_entId)
	{
		auto comp = m_components.find(a_entId);

        if(comp == m_components.end())
        {
			return nullptr;
        }

		return comp->second;
	}

    template <class C>
	std::map<EntityID, C*> ComponentContainer<C>::GetComponents()
	{
		return m_components;
	}
    
    template <class C>
    BaseComponent* ComponentContainer<C>::GetBaseComponent(const EntityID a_entId)
	{
        auto comp = m_components.find(a_entId);

        if(comp == m_components.end())
        {
			return nullptr;
        }

        return dynamic_cast<BaseComponent*>(comp->second);
	}
}