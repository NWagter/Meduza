#pragma once
#include "Platform/General/ContextBase.h"

namespace Me
{
    namespace Renderer
    {
        namespace GL
        {
            class Context : public ContextBase
            {
            public:
                Context(Window&);
                ~Context();

                void Resize(float,float) override;
                void SwapBuffer();

                float m_width, m_height;
            private:
                HWND m_hwnd;
                HDC m_hdc;
                HGLRC m_renderContext;
            };
        }       
    }
}