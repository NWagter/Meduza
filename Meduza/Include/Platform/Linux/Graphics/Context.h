#pragma once
#include "Platform/General/ContextBase.h"

struct WindowData;

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

                void InitContext(WindowData&, float, float);

                void Resize(float const a_width,float const a_height) override;
                void SwapBuffer();

                float m_width, m_height;
            private:
                GLXContext m_glContext;
                WindowData* m_windowData;
                XVisualInfo* m_visualInfo;
            };
        }       
    }
}