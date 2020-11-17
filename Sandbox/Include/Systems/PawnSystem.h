#pragma once

#include "ECS/BaseSystem.h"
#include "Components/PawnComponent.h"

namespace Me
{    
    struct TransformComponent;
}

class PawnSystem : public Me::BaseSystem<PawnComponent, Me::TransformComponent>
{
    public:
    PawnSystem();

    protected:
        void OnUpdate(float) override;

};