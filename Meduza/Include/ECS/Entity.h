#pragma once

#include "EntityTypes.h"

namespace Me
{
    struct BaseComponent;
    class EntityManager;

    class Entity
    {
    public:
        Entity();
        ~Entity();

        BaseComponent* GetComponent(ComponentID);
        bool HasComponent(ComponentID);
    private:
        std::map<ComponentID, BaseComponent*> m_components;

        bool AddComponent(BaseComponent*);
        bool RemoveComponent(ComponentID);

    friend EntityManager;
    };
}