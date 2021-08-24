#pragma once

#include "Platform/General/Graphics/RenderLayer.h"

namespace Me 
{
    class Window;

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

                struct Renderable
                {
                    RenderComponent* m_renderComponent;
                    Math::Mat4 m_modelMatrix;
                };
                
                struct Camera
                {
                    Math::Mat4 m_cameraMatrix;
                };

                RenderLayerGL(Window*);
                ~RenderLayerGL();

                void Clear(Colour) override;
                void Populate() override;    
                void Present() override;                
                void Submit(RenderComponent&, TransformComponent&) override;
                void SetCamera(CameraComponent&, TransformComponent&) override;

                Resources::GL::Mesh* CreateMesh(std::vector<Vertex>, std::vector<uint16_t>);
                
                Window* GetWindow() {return m_window;}
            private:
                Window* m_window;
                Context* m_context;

                std::vector<Renderable*> m_renderables;
                Resources::GL::Shader* m_activeShader;
                Camera* m_camera;
            };
        }
    }
}