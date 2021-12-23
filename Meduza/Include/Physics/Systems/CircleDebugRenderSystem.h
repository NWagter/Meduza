#pragma once

#include "ECS/BaseSystem.h"
namespace Me
{
    namespace Renderer
    {
        class RenderLayer;
    }

    struct TransformComponent;
    struct DebugRenderComponent;

    namespace Physics
    {
        struct CircleColliderComponent;
    }

    class CircleDebugRenderSystem : public BaseSystem<TransformComponent, DebugRenderComponent, Physics::CircleColliderComponent>
    {
    private:
        Colour m_debugColour;

    public:
        CircleDebugRenderSystem();

    protected:
        void OnUpdate(float a_dt) override;

    };
}