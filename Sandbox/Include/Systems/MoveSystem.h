#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{    
    struct TransformComponent;
}

struct MoveComponent;

class MoveSystem : public Me::BaseSystem<MoveComponent, Me::TransformComponent>
{
    public:
    MoveSystem();

    protected:
        void Update(float) override;

};