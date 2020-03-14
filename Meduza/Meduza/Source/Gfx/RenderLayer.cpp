#include "cepch.h"
#include "Gfx/RenderLayer.h"

#include "Gfx/Camera.h"

#include "Core/Core.h"
#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/DX12_RenderLayer.h"
static cr::RenderAPI gs_currentAPI = cr::RenderAPI::DX12;
#else 
#include "Platform/Switch/NVN_RenderLayer.h"
static cr::RenderAPI gs_currentAPI = cr::RenderAPI::NVN;
#endif


cr::RenderLayer * cr::RenderLayer::CreateRenderLayer(cr::Window& a_window)
{
	switch (gs_currentAPI)
	{
	case RenderAPI::None:
		CE_GFX_WARN("Can't create render layer no API defined");
		return nullptr;
	case RenderAPI::DX12:
#ifdef PLATFORM_WINDOWS
		CE_GFX_INFO("DX12 render layer generated");
		return new DX12_RenderLayer(a_window);
#else // 
		CE_GFX_WARN("Can't Create Window no API defined");
		return nullptr;
#endif
	case RenderAPI::NVN:
#ifdef PLATFORM_SWITCH
		return new NVN_RenderLayer(a_window);
		CE_CORE_ASSERT_M(false, "Text");
#else // 
		CE_GFX_WARN("Can't Create for Switch no API defined");
		return nullptr;
#endif
		break;
	}

	return nullptr;
}

cr::RenderAPI cr::RenderLayer::GetUsedAPI()
{
	return gs_currentAPI;
}
