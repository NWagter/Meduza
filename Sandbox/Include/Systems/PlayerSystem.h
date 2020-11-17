#pragma once

#include "ECS/BaseSystem.h"

#include "Components/PlayerComponent.h"
#include "Components/CursorComponent.h"

namespace Me
{
    struct TransformComponent;
}

class PlayerSystem : public Me::BaseSystem<PlayerComponent>
{
    public:
    PlayerSystem();


    protected:
        void OnCreate() override;
        void OnUpdate(float) override;
};