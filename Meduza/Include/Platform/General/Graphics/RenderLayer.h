#pragma once
namespace Me
{
    class Window;

    struct RenderComponent;
    struct CameraComponent;
    struct TransformComponent;

    namespace Renderer
    {
        class RenderLayer
        {
            public:
            static RenderLayer* CreateRenderer(Window*);

            virtual ~RenderLayer() = default;

            virtual void Clear(Colour) = 0;
            virtual void Populate() = 0;
            virtual void Present() = 0;
            virtual void Submit(RenderComponent&, TransformComponent&) = 0;
            virtual void SetCamera(CameraComponent&, TransformComponent&) = 0;
        };
    }
    
} // namespace Meduza
