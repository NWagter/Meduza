#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{    
    
    struct TransformComponent;

    namespace AI
    {
        struct AgentComponent;

        class AgentMovementSystem : public BaseSystem<TransformComponent, AgentComponent>
        {
            public:
                AgentMovementSystem();
                ~AgentMovementSystem();

            protected:
                void OnUpdate(float a_dt) override;  
        };
    }
}