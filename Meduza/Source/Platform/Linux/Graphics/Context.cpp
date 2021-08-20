#include "MePCH.h"
#include "Platform/Linux/Graphics/Context.h"

#include "Platform/Linux/LinuxWindow.h"

Me::Renderer::GL::Context::Context(Window& a_window) : Me::Renderer::ContextBase(a_window)
{
    static_cast<LinuxWindow*>(&a_window)->SetContext(this);
}

Me::Renderer::GL::Context::~Context()
{

}

void Me::Renderer::GL::Context::InitContext(WindowData& a_data, float a_w,float a_h)
{
    m_windowData = &a_data;

    m_width = a_w;
    m_height = a_h;

    GLint att[] = {
        GLX_RGBA,
        GLX_DEPTH_SIZE,
        24,
        GLX_DOUBLEBUFFER,
        None};
        

    m_visualInfo = glXChooseVisual(m_windowData->m_display, 0, att);

    m_glContext = glXCreateContext(m_windowData->m_display, m_visualInfo, NULL, GL_TRUE);
    glXMakeCurrent(m_windowData->m_display, m_windowData->m_window, m_glContext);

    int gladVersion = gladLoadGL();
    if(!gladVersion)
    {
        return;
    }

    glEnable(GL_DEPTH_TEST);
}

void Me::Renderer::GL::Context::Resize(float a_w,float a_h)
{
    if(m_windowData == nullptr)
    {
        return;
    }

    m_width = a_w;
    m_height = a_h;

}

void Me::Renderer::GL::Context::SwapBuffers()
{
    if(m_windowData == nullptr)
    {
        return;
    }

    glXSwapBuffers(m_windowData->m_display, m_windowData->m_window);
}