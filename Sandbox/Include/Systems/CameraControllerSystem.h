#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    struct TransformComponent;
    struct CameraComponent;
}

class CameraControllerSystem : public Me::BaseSystem<Me::TransformComponent,Me::CameraComponent>
{
    public:
    CameraControllerSystem();


    protected:
        void OnCreate() override;
        void OnUpdate(float) override;
};