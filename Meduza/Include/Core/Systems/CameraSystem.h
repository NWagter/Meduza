#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    namespace Renderer
    {
        class RenderLayer;
    }

    class CameraSystem : public BaseSystem
    {
    private:
        Renderer::RenderLayer* m_renderLayer;

    public:
        CameraSystem(Renderer::RenderLayer*);
        
    protected:
        void Update(float) override;
        void SetFilter() override;
        
    };
}