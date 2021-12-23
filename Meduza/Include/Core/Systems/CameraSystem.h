#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    namespace Renderer
    {
        class RenderLayer;
    }

    struct CameraComponent;
    struct TransformComponent;

    class CameraSystem : public BaseSystem<CameraComponent,TransformComponent>
    {
    private:
        Renderer::RenderLayer* m_renderLayer;

    public:
        CameraSystem(Renderer::RenderLayer* a_renderLayer);
        
    protected:
        void OnUpdate(float a_dt) override;        
    };
}