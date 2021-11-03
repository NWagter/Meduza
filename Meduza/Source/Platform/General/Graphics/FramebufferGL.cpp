#include "MePCH.h"
#include "Platform/General/Graphics/FramebufferGL.h"

#include "Platform/General/ContextBase.h"

Me::Renderer::GL::FrameBufferGL::FrameBufferGL(const FrameBufferSpecs& a_spec, ContextBase& a_context) : m_spec(a_spec)
{
    m_context = &a_context;
    Create();
}
Me::Renderer::GL::FrameBufferGL::~FrameBufferGL()
{
    glDeleteFramebuffers(1, &m_renderTextureID);
    glDeleteTextures(1, &m_colourAttachment);
    glDeleteTextures(1, &m_depthAttachment);
}

void Me::Renderer::GL::FrameBufferGL::Create()
{
    glGenFramebuffers(1, &m_renderTextureID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_renderTextureID);
    
    glGenTextures(1, &m_colourAttachment);
    glBindTexture(GL_TEXTURE_2D, m_colourAttachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
        m_spec.m_size.m_x, m_spec.m_size.m_y,
        0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colourAttachment, 0);
    
    glGenTextures(1, &m_depthAttachment);
    glBindTexture(GL_TEXTURE_2D, m_depthAttachment);
    glTexImage2D(GL_TEXTURE_2D,0, GL_DEPTH24_STENCIL8, 
        m_spec.m_size.m_x, m_spec.m_size.m_y, 0,
        GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachment, 0);
    
    ME_GFX_ASSERT_M(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Frame buffer not complete!");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    m_context->Resize(m_spec.m_size.m_x,m_spec.m_size.m_y);

}

void Me::Renderer::GL::FrameBufferGL::Resize(Math::Vec2 a_size)
{

    if( m_renderTextureID)
    {
        glDeleteFramebuffers(1, &m_renderTextureID);
        glDeleteTextures(1, &m_colourAttachment);
        glDeleteTextures(1, &m_depthAttachment);
    }

    m_spec.m_size = a_size;
    if(m_spec.m_size.m_x < 1)
    {
        m_spec.m_size.m_x = 1;
    }
    if(m_spec.m_size.m_y < 1)
    {
        m_spec.m_size.m_y = 1;
    }

    Create();
}

void Me::Renderer::GL::FrameBufferGL::Bind()
{
#ifdef PLATFORM_WINDOWS
    glBindFramebuffer(GL_FRAMEBUFFER, m_renderTextureID);
#endif
}

void Me::Renderer::GL::FrameBufferGL::UnBind()
{
#ifdef PLATFORM_WINDOWS
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif
}
