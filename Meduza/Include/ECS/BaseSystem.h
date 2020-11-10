#pragma once

#include "ECS/EntityTypes.h"

namespace Me
{
    class EntityManager;
    class BaseComponent;

    class BaseSystem
    {
    public:
        BaseSystem();
        virtual ~BaseSystem() = default;

    protected:
        virtual void SetFilter() = 0;
        virtual void Update(float) = 0;

        EntityFilter m_filter;
        std::vector<EntityID> m_entities;
    private:
        friend EntityManager;
    };
}