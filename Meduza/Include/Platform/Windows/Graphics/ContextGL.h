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
                Context(Window& a_window);
                ~Context();

                void Resize(float const a_width, float const a_heigt) override;
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