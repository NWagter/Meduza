#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    namespace Renderer
    {
        class RenderLayer;
    }

    struct RenderComponent;

    class RenderSystem : public BaseSystem
    {
    private:
        Renderer::RenderLayer* m_renderLayer;
        std::vector<RenderComponent*> m_components;
    public:
        RenderSystem(Renderer::RenderLayer*);
        
    protected:
        void Update(float) override;
        void SetFilter() override;
        
    };
}