#pragma once

#include "ECS/BaseSystem.h"
namespace Me
{
    namespace Renderer
    {
        class RenderLayer;
    }

    struct RenderComponent;
    struct TransformComponent;

    class RenderSystem : public BaseSystem<RenderComponent,TransformComponent>
    {
    private:
        Renderer::RenderLayer* m_renderLayer;
    public:
        RenderSystem(Renderer::RenderLayer* a_renderLayer);
        
    protected:
        void OnUpdate(float a_dt) override;
        
    };
}