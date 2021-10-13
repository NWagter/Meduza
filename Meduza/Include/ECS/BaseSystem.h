#pragma once

#include "ECS/EntityTypes.h"
#include "EntityManager.h"

#define EXECUTE_INGAME 1
#define EXECUTE_INEDITOR 2
#define EXECUTE_ALL 4

namespace Me
{
    class BaseComponent;

    class ECSSystem
    {
    public:
        ECSSystem();
        virtual ~ECSSystem() = default;

    protected:
        virtual void OnCreate() {}
        virtual void OnStart() {}
        virtual void OnUpdate(float) = 0;
        virtual void OnEntityCreated(const EntityID& a_entity) = 0;
        virtual void OnEntityDestroy(const EntityID& a_entity) = 0;

        std::vector<EntityID> m_entities;
        unsigned char m_executeMask = EXECUTE_INGAME;

    private:
        bool m_OnCreated = false;
        friend EntityManager;
    };

    
    template<class... Comps>
    class BaseSystem : public ECSSystem
    {
    protected:
        using CompTuple = std::tuple<std::add_pointer_t<Comps>...>;
        std::vector<CompTuple> m_components;
        
        void OnEntityCreated(const EntityID& a_entity) override final;
        void OnEntityDestroy(const EntityID& a_entity) override final;

    public:
        virtual ~BaseSystem() = default;

    private:


        template<size_t INDEX, class CompType, class... CompArgs>
        bool ProcessEntityComponent(ComponentID a_compId, BaseComponent* a_component, CompTuple& a_tupleToFill);
        template<size_t INDEX>
        bool ProcessEntityComponent(ComponentID a_compId, BaseComponent* a_component, CompTuple& a_tupleToFill);
    };

    template<class... Comps>
    void BaseSystem<Comps...>::OnEntityCreated(const EntityID& a_entity)
    {
        CompTuple compTuple;
        size_t matchingComps = 0;
        auto ent = EntityManager::GetEntityManager()->GetEntities().at(a_entity);
        for(auto& compId : ent)
        {
            for(auto& container : EntityManager::GetEntityManager()->GetContainers())
            {
                if(container.first == compId)
                {
                    if(ProcessEntityComponent<0, Comps...>(compId, container.second->GetBaseComponent(a_entity), compTuple))
                    {
                        ++matchingComps;
                        if(matchingComps == sizeof...(Comps))
                        {
                            m_components.emplace_back(std::move(compTuple));
                            m_entities.push_back(a_entity);
                            break;
                        }
                    }
                }
            }
        }
        
    }

    template<class... Comps>
    template<size_t INDEX, class CompType, class... CompArgs>
    bool BaseSystem<Comps...>::ProcessEntityComponent(ComponentID a_compId, BaseComponent* a_component, CompTuple& a_tupleToFill)
    {
        if(CompType::s_componentID == a_compId)
        {
            std::get<INDEX>(a_tupleToFill) = static_cast<CompType*>(a_component);
            return true;
        }
        else
        {
            return ProcessEntityComponent<INDEX + 1, CompArgs...>(a_compId, a_component, a_tupleToFill);
        }
    }

    template<class... Comps>
    template<size_t INDEX>
    bool BaseSystem<Comps...>::ProcessEntityComponent(ComponentID, BaseComponent*, CompTuple&)
    {
        return false;
    }


    template<class... Comps>
    void BaseSystem<Comps...>::OnEntityDestroy(const EntityID& a_entity)
    {
        auto it = std::find(m_entities.begin(), m_entities.end(), a_entity);
        
        int index = std::distance(m_entities.begin(), it);
        
        m_components.erase(m_components.begin() + index);
        m_entities.erase(m_entities.begin() + index);
    }


}