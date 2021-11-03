#include "MePCH.h"
#include "Platform/Windows/Graphics/FramebufferDx12.h"

#include "Platform/Windows/Graphics/ContextDx.h"
#include "Platform/Windows/Graphics/Descriptor.h"

Me::Renderer::Dx12::FrameBufferDx12::FrameBufferDx12(const FrameBufferSpecs& a_spec, ContextBase& a_context) : m_spec(a_spec)
{
    m_attachment = nullptr;
    m_context = &a_context;
}
Me::Renderer::Dx12::FrameBufferDx12::~FrameBufferDx12()
{
    delete m_attachment;
}


void Me::Renderer::Dx12::FrameBufferDx12::Resize(Math::Vec2 a_size)
{

}

Me::Renderer::ColourAttachment* Me::Renderer::Dx12::FrameBufferDx12::GetColourAttachment()
{
    if(m_attachment == nullptr)
    {
        m_attachment = new ColourAttachmentDx12();
    }
    auto frameBuffer = static_cast<Context*>(m_context)->GetRTV();
    m_attachment->m_api = GFX_API::DX12;
    m_attachment->m_texture = CD3DX12_GPU_DESCRIPTOR_HANDLE(frameBuffer->GetHeap()->GetGPUDescriptorHandleForHeapStart());

    return m_attachment;
}
