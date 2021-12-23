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
        struct BoxCollider2DComponent;
    }

    class Box2DDebugRenderSystem : public BaseSystem<TransformComponent, DebugRenderComponent, Physics::BoxCollider2DComponent>
    {
    private:
        Renderer::RenderLayer* m_renderLayer;
        Shader m_debugShader;
        Mesh m_debugMesh;
        Colour m_debugColour;
        
    public:
        Box2DDebugRenderSystem(Renderer::RenderLayer* a_renderLayer);
        
    protected:
        void OnUpdate(float a_dt) override;
        
    };
}