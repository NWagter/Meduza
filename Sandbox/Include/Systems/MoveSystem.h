#pragma once

#include "ECS/BaseSystem.h"

#include "Components/MoveComponent.h"

namespace Me
{    
    struct TransformComponent;
}

class MoveSystem : public Me::BaseSystem<MoveComponent, Me::TransformComponent>
{
    public:
    MoveSystem();

    protected:
        void OnUpdate(float) override;

};