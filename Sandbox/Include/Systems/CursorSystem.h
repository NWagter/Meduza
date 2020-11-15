#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    struct TransformComponent;
    struct RenderComponent;
}

struct CursorComponent;

class CursorSystem : public Me::BaseSystem<CursorComponent, Me::TransformComponent>
{
    public:
    CursorSystem();

    protected:
        void OnCreate() override;
        void OnUpdate(float) override;

};