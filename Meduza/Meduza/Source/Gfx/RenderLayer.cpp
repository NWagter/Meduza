#include "mePch.h"

#include "Gfx/RenderLayer.h"
#include "Gfx/Window.h"

#ifdef PLATFORM_WINDOWS
static mr::RenderAPI gs_currentRenderAPI = mr::RenderAPI::DX12;
#include "Platform/Windows/DirectX12/DX12_RenderLayer.h"
#endif // PLATFORM_WINDOWS


mr::RenderLayer* mr::RenderLayer::CreateRenderLayer(Window& a_window)
{
	
	switch (gs_currentRenderAPI)
	{
	case mr::RenderAPI::None:
		break;
	case mr::RenderAPI::DX12:
		return new DX12_Renderlayer(a_window);
		break;
	default:
		break;
	}
	return nullptr;
}

mr::RenderAPI mr::RenderLayer::GetAPI()
{
	return gs_currentRenderAPI;
}
