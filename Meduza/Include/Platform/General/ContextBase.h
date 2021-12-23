#pragma once

namespace Me
{
    class Window;

    namespace Renderer
    {
        class ContextBase
        {
            public:
            ContextBase(Window& a_windows);
            virtual ~ContextBase();
            
            virtual void Resize(float const a_width, float const a_height) = 0;
        };
    }
}