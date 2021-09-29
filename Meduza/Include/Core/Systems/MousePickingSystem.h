#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    struct TransformComponent;
    struct CameraComponent;

    class MousePickingSystem : public BaseSystem<CameraComponent,TransformComponent>
    {
    public:
        MousePickingSystem();
        
    protected:
        void OnUpdate(float) override;        
    };
}