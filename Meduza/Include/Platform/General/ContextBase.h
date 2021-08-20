#pragma once

namespace Me
{
    class Window;

    namespace Renderer
    {
        class ContextBase
        {
            public:
            ContextBase(Window&);
            virtual ~ContextBase();
            
            virtual void Resize(float,float) = 0;
        };
    }
}