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
        struct BoxCollider3DComponent;
    }

    class Box3DDebugRenderSystem : public BaseSystem<TransformComponent, DebugRenderComponent, Physics::BoxCollider3DComponent>
    {
    private:
        Renderer::RenderLayer* m_renderLayer;
        Shader m_debugShader;
        Mesh m_debugMesh;
        Colour m_debugColour;
        
    public:
        Box3DDebugRenderSystem(Renderer::RenderLayer* a_renderLayer);

        ThreadType GetThreadType() const override { return ThreadType::RenderCommand; }
        
    protected:
        void OnUpdate(float a_dt) override;
        
    };
}