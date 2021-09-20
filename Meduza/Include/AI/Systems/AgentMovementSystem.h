#pragma once

#include "ECS/BaseSystem.h"
#include "AI/Components/AgentComponent.h"

namespace Me
{    
    
    struct TransformComponent;

    namespace AI
    {
        class AgentMovementSystem : public BaseSystem<TransformComponent, AgentComponent>
        {
            public:
                AgentMovementSystem();
                ~AgentMovementSystem();

            protected:
                void OnUpdate(float) override;  
        };
    }
}