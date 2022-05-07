#pragma once

#include "Platform/General/Graphics/RenderLayer.h"

namespace Me 
{
    class Window;

    namespace Resources
    {
        class MeshBase;

        namespace GL
        {
            class Shader;
        }
    }

    namespace Renderer
    {
        class FrameBuffer;
        class BaseInstanced;
        
        namespace GL
        {
            struct DefaultInstancedBuffer
            {
                Math::Matrix4 m_model = Math::Matrix4::Identity();
                Math::Vector4 m_colour = Math::Vector4(1, 0, 1, 1);
                Math::Vector4 m_textureCoords = Math::Vector4(0, 0, 1, 1);
                float m_textureId = 0;
            };

            class Context;

            class RenderLayerGL : public RenderLayer
            {
            public:

                struct Renderable
                {
                    RenderComponent* m_renderComponent;
                    Math::Matrix4 m_modelMatrix;
                };

                struct DebugRenderable
                {
                    DebugRenderComponent* m_debugRenderComponent;
                    Math::Matrix4 m_modelMatrix;
                };

                struct DebugLine
                {
                    unsigned int m_vbo;
                    unsigned int m_vao;

                    Colour m_colour;

                    DebugLine(unsigned int a_vbo, unsigned int a_vao, Colour a_colour = Colours::MAGENTA)
                    {
                        m_vbo = a_vbo;
                        m_vao = a_vao;

                        m_colour = a_colour;
                    }

                    ~DebugLine()
                    {
                        glDeleteVertexArrays(1, &m_vao);
                        glDeleteBuffers(1, &m_vbo);
                    }
                };
                struct DebugCricle
                {
                    Math::Matrix4 m_trans;
                    float m_radius;
                    Colour m_colour;

                    DebugCricle(Math::Matrix4 const& a_trans, float const& a_rad, Colour const& a_colour = Colours::MAGENTA)
                    {
                        m_trans = a_trans;
                        m_radius = a_rad * 2;
                        m_colour = a_colour;
                    }
                };

                struct Camera
                {
                    Math::Matrix4 m_cameraMatrix;
                };

                RenderLayerGL(Window* a_window);
                ~RenderLayerGL();

                void Init() override;
                void Clear(Colour const a_clearColour) override;
                void Populate() override;    
                void Present() override;                
                void Submit(RenderComponent const& a_renderComponent, TransformComponent& a_transformComponent) override;
                void DebugSubmit(DebugRenderComponent const& a_debugRenderComponent, TransformComponent& a_transformComponent) override;
                void RenderLine(LineRender const& a_lineRender) override;
                void RenderCircle(CircleRender const& a_circleRender)  override;
                void SetCamera(CameraComponent const& a_cameraComponent, TransformComponent& a_transformComponent) override;

                Resources::MeshBase* CreateMesh(std::vector<Vertex> const& a_vertices, std::vector<uint16_t> const& a_indices);
                
                Window* GetWindow() override {return m_window;}
            private:
                Window* m_window;
                Context* m_context;

                std::vector<BaseInstanced*> m_instances;
                std::vector<BaseInstanced*> m_debugInstances;

                std::vector<DebugLine*> m_debugLines;
                std::vector<DebugCricle*> m_debugCircle;
                Resources::GL::Shader* m_activeShader;

                Camera* m_camera;
                Shader m_screenShader;
                Shader m_lineShader;
                Shader m_circleShader;
                Mesh m_quad;
            };
        }
    }
}