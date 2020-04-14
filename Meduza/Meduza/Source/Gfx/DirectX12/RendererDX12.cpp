#include "mePch.h"

#include "Gfx/DirectX12/RendererDX12.h"

meduza::renderer::RendererDX12::RendererDX12()
{
	printf("Create DX12 Renderer \n");
}

meduza::renderer::RendererDX12::~RendererDX12()
{
	printf("Delete DX12 Renderer \n");
}

void meduza::renderer::RendererDX12::Clear(Colour)
{
}

void meduza::renderer::RendererDX12::Draw(Sprite)
{
}

void meduza::renderer::RendererDX12::Draw(Mesh)
{
}

void meduza::renderer::RendererDX12::Draw(Text)
{
}

void meduza::renderer::RendererDX12::Render()
{
}
