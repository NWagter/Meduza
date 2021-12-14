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
        class FrameBuffer;
        class BaseInstanced;
        
        namespace GL
        {
            struct DefaultInstancedBuffer
            {
                Math::Mat4 m_model = Math::Mat4::Identity();
                Math::Vec4 m_colour = Math::Vec4(1, 0, 1, 1);
                Math::Vec4 m_textureCoords = Math::Vec4(0, 0, 1, 1);
                float m_textureId = 0;
            };

            class Context;

            class RenderLayerGL : public RenderLayer
            {
            public:

                struct Renderable
                {
                    RenderComponent* m_renderComponent;
                    Math::Mat4 m_modelMatrix;
                };

                struct DebugRenderable
                {
                    DebugRenderComponent* m_debugRenderComponent;
                    Math::Mat4 m_modelMatrix;
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
                    Math::Mat4 m_trans;
                    float m_radius;
                    Colour m_colour;

                    DebugCricle(Math::Mat4& a_trans, float a_rad, Colour a_colour = Colours::MAGENTA)
                    {
                        m_trans = a_trans;
                        m_radius = a_rad * 2;
                        m_colour = a_colour;
                    }
                };

                struct Camera
                {
                    Math::Mat4 m_cameraMatrix;
                };

                RenderLayerGL(Window*);
                ~RenderLayerGL();

                void Init() override;
                void Clear(Colour) override;
                void Populate() override;    
                void Present() override;                
                void Submit(RenderComponent&, TransformComponent&) override;
                void DebugSubmit(DebugRenderComponent&, TransformComponent&) override;
                void RenderLine(LineRender&) override;
                void RenderCircle(CircleRender&)  override;
                void SetCamera(CameraComponent&, TransformComponent&) override;

                Resources::GL::Mesh* CreateMesh(std::string, std::vector<Vertex>, std::vector<uint16_t>);
                
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