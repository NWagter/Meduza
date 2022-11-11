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
        struct SphereColliderComponent;
    }

    class SphereDebugRenderSystem : public BaseSystem<TransformComponent, DebugRenderComponent, Physics::SphereColliderComponent>
    {
    private:
        Renderer::RenderLayer* m_renderLayer;
        Shader m_debugShader;
        Mesh m_debugMesh;
        Colour m_debugColour;
        
    public:
        SphereDebugRenderSystem(Renderer::RenderLayer* a_renderLayer);

        ThreadType GetThreadType() const override { return ThreadType::Render; }
        
    protected:
        void OnUpdate(float a_dt) override;
        
    };
}