#include "MePCH.h"
#include "Platform/Windows/Graphics/FramebufferDx12.h"

#include "Platform/Windows/Graphics/ContextDx.h"
#include "Platform/Windows/Graphics/Descriptor.h"
#include "Platform/Windows/Graphics/RenderLayerDx12.h"

Me::Renderer::Dx12::FrameBufferDx12::FrameBufferDx12(FrameBufferSpecs const& a_spec, ContextBase& a_context) : m_spec(a_spec)
{
    m_attachment = nullptr;
    m_context = &a_context;
}
Me::Renderer::Dx12::FrameBufferDx12::~FrameBufferDx12()
{
    delete m_attachment;
}


void Me::Renderer::Dx12::FrameBufferDx12::Resize(Math::Vec2 const& a_size)
{

}

Me::Renderer::ColourAttachment* Me::Renderer::Dx12::FrameBufferDx12::GetColourAttachment()
{
    if(m_attachment == nullptr)
    {
        m_attachment = new ColourAttachmentDx12();
    }
    m_attachment->m_api = GFX_API::DX12;
    auto srv = static_cast<RenderLayerDx12*>(Renderer::RenderLayer::GetRenderLayer())->GetSRV();
    D3D12_GPU_DESCRIPTOR_HANDLE handle = srv.GetHeap()->GetGPUDescriptorHandleForHeapStart();
    m_attachment->m_texture = handle;
    return m_attachment;
}
