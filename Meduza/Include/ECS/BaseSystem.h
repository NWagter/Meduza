#pragma once

#include "ECS/EntityTypes.h"

namespace Me
{
    class EntityManager;

    class BaseSystem
    {
    public:
        virtual ~BaseSystem() = default;
        
        void AddComponentToFilter(ComponentID a_id)
        {
            if(std::find(m_filter.begin(), m_filter.end(), a_id) != m_filter.end())
            {
                return;
            }
            
            m_filter.push_back(a_id);
        }
    protected:
        virtual void Update(float) = 0;

        EntityFilter m_filter;
    private:
        friend EntityManager;
    };
}