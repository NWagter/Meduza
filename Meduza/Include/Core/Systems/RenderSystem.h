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
        RenderSystem(Renderer::RenderLayer*);
        
    protected:
        void OnUpdate(float) override;
        
    };
}