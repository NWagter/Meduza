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
            struct RenderData
            {
                Mesh m_mesh;
                Shader m_shader;
                Texture m_texture;
            };

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
                    Math::Vector3 m_begin;
                    Math::Vector3 m_end;

                    unsigned int m_vbo;
                    unsigned int m_vao;

                    Colour m_colour;

                    DebugLine(Math::Vector3 const a_begin, Math::Vector3 const a_end, Colour a_colour = Colours::MAGENTA)
                    {
                        m_begin = a_begin;
                        m_end = a_end;

                        m_colour = a_colour;
                    }

                    ~DebugLine()
                    {
                        glDeleteVertexArrays(1, &m_vao);
                        glDeleteBuffers(1, &m_vbo);
                    }

                    void GenerateBuffers()
                    {
                        std::vector<float> vertices = {
                            m_begin.m_x, m_begin.m_y, m_begin.m_z,
                            m_end.m_x, m_end.m_y, m_end.m_z
                        };

                        glGenVertexArrays(1, &m_vao);
                        glGenBuffers(1, &m_vbo);
                        glBindVertexArray(m_vao);

                        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
                        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

                        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
                        glEnableVertexAttribArray(0);

                        glBindBuffer(GL_ARRAY_BUFFER, 0);
                        glBindVertexArray(0);
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
                void AddToInstance(DefaultInstancedBuffer a_data, RenderData a_renderData, RenderType const a_renderType);
                Window* m_window;
                Context* m_context;

                std::map<RenderType, std::vector<BaseInstanced*>> m_instanceMap;

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