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
        class FrameBuffer;

        class RenderLayer
        {
            public:
                static RenderLayer* CreateRenderer(Window*, GFX_API = GFX_API::Unknown);

                virtual ~RenderLayer() = default;

                virtual void Init() {}
                virtual void Clear(Colour) = 0;
                virtual void Populate() = 0;
                virtual void Present() = 0;
                virtual void Submit(RenderComponent&, TransformComponent&) = 0;
                virtual void DebugSubmit(DebugRenderComponent&, TransformComponent&) = 0;
                virtual void SetCamera(CameraComponent&, TransformComponent&) = 0;

                static GFX_API GetAPI() { return ms_api;}
                
                virtual Window* GetWindow() = 0;
                FrameBuffer* GetFrameBuffer() {return m_frameBuffer;}

            private:
                static GFX_API ms_api;
            protected:
                FrameBuffer* m_frameBuffer;
        };
    }
    
} // namespace Meduza
