#pragma once
namespace Me
{
    class Window;

    struct RenderComponent;
    struct DebugRenderComponent;
    struct CameraComponent;
    struct TransformComponent;
    namespace Renderer
    {
        struct LineRender
        {
            Math::Vector3 m_start;
            Math::Vector3 m_end;
            Colour m_colour;
        };        
        struct CircleRender
        {
            Math::Matrix4 m_transform;
            float m_radius;
            Colour m_colour;
        };


        class FrameBuffer;

        struct RenderStats
        {
            int m_drawCalls = 0;
            int m_vertices = 0;

            void Reset()
            {
                m_drawCalls = 0;
                m_vertices = 0;
            }
        };

        class RenderLayer
        {
            public:
                static RenderLayer* CreateRenderer(Window* a_window, GFX_API a_api = GFX_API::Unknown);

                virtual ~RenderLayer() = default;

                virtual void Init() {}
                virtual void Clear(Colour const a_clearColour) = 0;
                virtual void Populate() = 0;
                virtual void Present() = 0;
                virtual void Submit(RenderComponent const& a_renderComponent, TransformComponent const& a_transformComponent) = 0;
                virtual void DebugSubmit(DebugRenderComponent const& a_debugRenderComponent, TransformComponent const& a_transformComponent) = 0;
                virtual void RenderLine(LineRender const& a_lineRender) = 0;
                virtual void RenderCircle(CircleRender const& a_circleRender) = 0;
                virtual void SetCamera(CameraComponent const& a_cameraComponnet, TransformComponent const& a_transformComponent) = 0;

                static GFX_API GetAPI() { return ms_api;}
                static RenderLayer* GetRenderLayer() { return ms_instance; };
                
                virtual Window* GetWindow() = 0;
                FrameBuffer* GetFrameBuffer() {return m_frameBuffer;}
                inline RenderStats GetRenderStats() const { return m_renderStats; }

            private:
                static GFX_API ms_api;
                static RenderLayer* ms_instance;
            protected:
                FrameBuffer* m_frameBuffer;
                RenderStats m_renderStats;
        };
    }
    
} // namespace Meduza
