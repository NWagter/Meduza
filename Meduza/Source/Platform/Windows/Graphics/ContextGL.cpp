#include "MePCH.h"

#include "Platform/Windows/Graphics/ContextGL.h"
#include "Platform/Windows/WindowsWindow.h"

#pragma comment(lib,"OpenGL32.lib")

Me::Renderer::GL::Context::Context(Window& a_window) : Me::Renderer::ContextBase(a_window)
{
    m_width = a_window.GetSize().m_x;
    m_height = a_window.GetSize().m_y;

    m_hwnd = static_cast<WindowsWindow*>(&a_window)->GetWindowHandle();

    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
        PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
        32,                   // Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,                   // Number of bits for the depthbuffer
        8,                    // Number of bits for the stencilbuffer
        0,                    // Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    m_hdc = GetDC(m_hwnd);

    int nPixelFormat = ChoosePixelFormat( m_hdc, &pfd );
    SetPixelFormat( m_hdc, nPixelFormat, &pfd );

    m_renderContext = wglCreateContext(m_hdc);
    wglMakeCurrent(m_hdc, m_renderContext);

    int gladVersion = gladLoadGL();
    if(!gladVersion)
    {
        return;
    }
}

Me::Renderer::GL::Context::~Context()
{
    
}

void Me::Renderer::GL::Context::Resize(float a_width, float a_height)
{
    m_width = a_width;
    m_height = a_height;
}

void Me::Renderer::GL::Context::SwapBuffer()
{
    SwapBuffers(m_hdc);
}