#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{    
    struct TransformComponent;
}

struct TileComponent;

class CheckboardSystem : public Me::BaseSystem<TileComponent, Me::TransformComponent>
{
    public:
    CheckboardSystem();

    protected:
        void OnCreate() override;
        void OnUpdate(float) override;

};