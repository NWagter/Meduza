#include "mePch.h"

#pragma comment( lib, "d3d12.lib" )
#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "d3dcompiler.lib" )
#pragma comment( lib, "dxguid.lib" )

#include "Gfx/DirectX12/RendererDX12.h"

#include "Platform/Windows/WinWindow.h"
#include "Gfx/DirectX12/DeviceDX12.h"

#include "Drawable/Drawable.h"
#include "Util/MeduzaHelper.h"

meduza::renderer::RendererDX12::RendererDX12(Window& a_window)
{
	printf("Create DX12 Renderer \n");

	m_window = &a_window;
	m_device = new DeviceDX12();
}

meduza::renderer::RendererDX12::~RendererDX12()
{
	printf("Delete DX12 Renderer \n");
	delete m_device;
}

void meduza::renderer::RendererDX12::Clear(Colour)
{
	
}

void meduza::renderer::RendererDX12::Submit(drawable::Drawable*)
{
}

void meduza::renderer::RendererDX12::Submit(std::vector<drawable::Drawable*> a_drawables)
{
	unsigned int size = unsigned int(a_drawables.size());

	printf("Amount of Drawables : %i", size);
}


void meduza::renderer::RendererDX12::Render()
{
}
