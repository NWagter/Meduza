#include "MePCH.h"
#include "Platform/Windows/Graphics/RenderLayerDx12.h"

#include "Platform/Windows/Helper/Helper.h"

#include "Platform/Windows/WindowsWindow.h"
#include "Platform/Windows/Graphics/ContextDx12.h"

#include "Platform/Windows/Graphics/Device.h"
#include "Platform/Windows/Graphics/CommandList.h"
#include "Platform/Windows/Graphics/CommandQueue.h"
#include "Platform/Windows/Graphics/Descriptor.h"

#include "Platform/General/ResourceLibrary.h"

#include "Core/Components/RenderComponent.h"
#include "Core/Components/CameraComponent.h"
#include "Core/Components/TransformComponent.h"

#include "Platform/Windows/Resources/Mesh.h"

#define TEST_WITH_DX_DEBUG 1

Me::Renderer::Dx12::RenderLayerDx12::RenderLayerDx12(Me::Window* a_window)
{
    if(a_window == nullptr)
    {
        printf("Window is Null!");
        return;
    }
    //cast the window into a WindowsWindow type
    m_window = dynamic_cast<WindowsWindow*>(a_window);

    m_device = new Device();
    m_context = new Context(*m_window, m_device);
    m_window->SetContext(m_context);

    CommandList* cmd = new CommandList(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT, 
        m_device, 
        m_window->GetSize().m_x, 
        m_window->GetSize().m_y);

    m_commandLists.push_back(cmd);
}

Me::Renderer::Dx12::RenderLayerDx12::~RenderLayerDx12()
{
    
}

void Me::Renderer::Dx12::RenderLayerDx12::Clear(Colour const a_clearColour)
{
	
}

void Me::Renderer::Dx12::RenderLayerDx12::Present()
{

}

void Me::Renderer::Dx12::RenderLayerDx12::Submit(RenderComponent const& a_renderable, TransformComponent& a_transformComponent)
{

}

void Me::Renderer::Dx12::RenderLayerDx12::DebugSubmit(DebugRenderComponent const&, TransformComponent&)
{

}


void Me::Renderer::Dx12::RenderLayerDx12::RenderLine(LineRender const&)
{

}

void Me::Renderer::Dx12::RenderLayerDx12::RenderCircle(CircleRender const&)
{

}

void Me::Renderer::Dx12::RenderLayerDx12::SetCamera(CameraComponent const& a_cameraComponent, TransformComponent& a_transformComponent)
{
}

void Me::Renderer::Dx12::RenderLayerDx12::Populate()
{
}

Me::Window* Me::Renderer::Dx12::RenderLayerDx12::GetWindow()
{
	return static_cast<Window*>(m_window);
}

Me::Resources::MeshBase* Me::Renderer::Dx12::RenderLayerDx12::CreateMesh(std::vector<Vertex> const& a_vertices, std::vector<uint16_t> const& a_indices)
{
	return new Me::Resources::Dx12::Mesh(a_vertices, a_indices, *m_device, GetCmd());
}

Me::Resources::Dx12::Texture* Me::Renderer::Dx12::RenderLayerDx12::LoadTexture(std::string const& a_file)
{
	return nullptr;
}

Me::Resources::Dx12::Texture* Me::Renderer::Dx12::RenderLayerDx12::LoadTexture(std::vector<unsigned char> const& a_texture, int const a_width, int const a_height)
{
	return nullptr;
}