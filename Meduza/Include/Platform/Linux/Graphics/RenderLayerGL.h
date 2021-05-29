#pragma once

#include "Platform/General/Graphics/RenderLayer.h"

namespace Me 
{
    class LinuxWindow;

    namespace Resources
    {
        namespace GL
        {
            class Mesh;
            class Shader;
        }
    }

    namespace Renderer
    {
        namespace GL
        {
            class Context;

            class RenderLayerGL : public RenderLayer
            {
            public:
                RenderLayerGL(Window*);
                ~RenderLayerGL();

                void Clear(Colour) override;
                void Populate() override;    
                void Present() override;                
                void Submit(RenderComponent&, TransformComponent&) override;
                void SetCamera(CameraComponent&, TransformComponent&) override;

                Resources::GL::Mesh* CreateMesh(std::vector<Vertex>, std::vector<uint16_t>);
                
            private:
                LinuxWindow* m_window;
                Context* m_context;

                std::vector<RenderComponent*> m_renderables;
                Resources::GL::Shader* m_activeShader;
            };
        }
    }
}