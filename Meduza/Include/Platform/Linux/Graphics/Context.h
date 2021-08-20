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
                Context(Window&);
                ~Context();

                void InitContext(WindowData&, float, float);

                void Resize(float,float) override;
                void SwapBuffers();

                float m_width, m_height;
            private:
                GLXContext m_glContext;
                WindowData* m_windowData;
                XVisualInfo* m_visualInfo;
            };
        }       
    }
}