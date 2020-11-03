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
                void Present() override;                
                void Submit(Renderable&) override;

                Resources::GL::Mesh* CreateMesh(std::vector<Vertex>, std::vector<uint16_t>);
            private:
                void Populate();
                LinuxWindow* m_window;
                Context* m_context;

                std::vector<Renderable*> m_renderables;
                Resources::GL::Shader* m_activeShader;
            };
        }
    }
}