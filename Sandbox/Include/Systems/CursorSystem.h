#pragma once

#include "ECS/BaseSystem.h"

#include "Components/CursorComponent.h"

namespace Me
{    
    struct TransformComponent;
}

class CursorSystem : public Me::BaseSystem<CursorComponent, Me::TransformComponent>
{
    public:
    CursorSystem();


    protected:
        void OnCreate() override;
        void OnUpdate(float) override;

};