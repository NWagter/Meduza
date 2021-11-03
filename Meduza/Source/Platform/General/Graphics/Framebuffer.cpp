#include "MePCH.h"
#include "Platform/General/Graphics/FrameBuffer.h"

#ifdef PLATFORM_WINDOWS

#include "Platform/General/Graphics/FramebufferGL.h"
#include "Platform/Windows/Graphics/FramebufferDx12.h"

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
    case GFX_API::DX12:
#ifdef PLATFORM_WINDOWS
        return new Dx12::FrameBufferDx12(a_spec, a_context);
#else
            ME_CORE_ASSERT_M(false, "This platform doesn't support DirectX12")
            return nullptr;
#endif
        break;
    
    default:
        return nullptr;
        break;
    }   
}