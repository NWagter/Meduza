#pragma once

#include "ECS/BaseComponent.h"

namespace Me
{
    namespace AI
    {
        struct AgentComponent : public BaseComponent
        {
            Math::Vec3 m_targetLocation;
            float m_agentSpeed;
            float m_stopDistance;

            static ComponentID s_componentID;
        };
        
    }
}