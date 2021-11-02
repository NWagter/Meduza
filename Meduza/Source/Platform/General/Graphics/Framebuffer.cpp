#include "MePCH.h"
#include "Platform/General/Graphics/FrameBuffer.h"

#ifdef PLATFORM_WINDOWS

#include "Platform/General/Graphics/FramebufferGL.h"

#elif PLATFORM_LINUX
#include "Platform/General/Graphics/FramebufferGL.h"
#elif PLATFORM_APPLE
#endif

Me::Renderer::FrameBuffer* Me::Renderer::FrameBuffer::Create(const FrameBufferSpecs& a_spec, ContextBase& a_context)
{
    switch (a_spec.m_api)
    {
    case GFX_API::OpenGL:
        return new GL::FrameBufferGL(a_spec, a_context);
        break;
    
    default:
        return nullptr;
        break;
    }   
}