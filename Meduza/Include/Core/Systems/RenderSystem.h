#pragma once

#include "ECS/BaseSystem.h"
#include "Core/Components/RenderComponent.h"
#include "Core/Components/TransformComponent.h"
namespace Me
{
    namespace Renderer
    {
        class RenderLayer;
    }

    class RenderSystem : public BaseSystem<RenderComponent,TransformComponent>
    {
    private:
        Renderer::RenderLayer* m_renderLayer;
    public:
        RenderSystem(Renderer::RenderLayer*);
        
    protected:
        void Update(float) override;
        
    };
}