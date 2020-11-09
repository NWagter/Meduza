#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    namespace Renderer
    {
        class RenderLayer;
    }

    class RenderSystem : public BaseSystem
    {
    private:
        Renderer::RenderLayer* m_renderLayer;

    public:
        RenderSystem(Renderer::RenderLayer*);
        
    protected:
        void Update(float) override;
        
    };
}