#pragma once
namespace Me
{
    class Window;

    struct RenderComponent;
    struct CameraComponent;
    struct TransformComponent;

    enum class GFX_API
    {
        Unknown,
        DX12,
        OpenGL
    };

    namespace Renderer
    {
        class RenderLayer
        {
            public:
                static RenderLayer* CreateRenderer(Window*, GFX_API = GFX_API::Unknown);

                virtual ~RenderLayer() = default;

                virtual void Clear(Colour) = 0;
                virtual void Populate() = 0;
                virtual void Present() = 0;
                virtual void Submit(RenderComponent&, TransformComponent&) = 0;
                virtual void SetCamera(CameraComponent&, TransformComponent&) = 0;

                static GFX_API GetAPI() { return ms_api;}

            private:
                static GFX_API ms_api;
        };
    }
    
} // namespace Meduza
