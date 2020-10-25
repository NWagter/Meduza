#pragma once
namespace Me
{
    class Window;

    struct Renderable;

    namespace Renderer
    {
        class RenderLayer
        {
            public:
            static RenderLayer* CreateRenderer(Window*);

            virtual ~RenderLayer() = default;

            virtual void Clear(Colour) = 0;
            virtual void Present() = 0;
            virtual void Submit(Renderable&) = 0;
        };
    }
    
} // namespace Meduza
