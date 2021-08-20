#include "MePCH.h"

#include "Platform/Windows/Graphics/ContextGL.h"
#include "Platform/Windows/WindowsWindow.h"

#pragma comment(lib,"OpenGL32.lib")

Me::Renderer::GL::Context::Context(Window& a_window) : Me::Renderer::ContextBase(a_window)
{
    m_width = a_window.GetSize().m_x;
    m_height = a_window.GetSize().m_y;

    m_hwnd = static_cast<WindowsWindow*>(&a_window)->GetWindowHandle();

    m_hdc = GetDC(m_hwnd);

    m_renderContext = wglCreateContext(m_hdc);
    wglMakeCurrent(m_hdc, m_renderContext);

}

Me::Renderer::GL::Context::~Context()
{
    
}

void Me::Renderer::GL::Context::Resize(float, float)
{

}

void Me::Renderer::GL::Context::SwapBuffer()
{
    SwapBuffers(m_hdc);
}