#include "cepch.h"
#include "Gfx/Window.h"
#include "Gfx/RenderLayer.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/WinWindow.h"
#elif PLATFORM_SWITCH
#include "Platform/Switch/NVNWindow.h"
#endif

cr::Window* cr::Window::CreateNewWindow(RenderAPI a_api, int a_width, int a_height)
{
	switch (a_api)
	{
	case RenderAPI::None:
		CE_GFX_WARN("Can't Create Window no API defined");
		return nullptr;
	case RenderAPI::DX12:
#ifdef PLATFORM_WINDOWS
		CE_GFX_INFO("Windows Window generated");
		return new WinWindow(a_width, a_height, "CE | WINDOWS | DX12");
#else // 
		CE_GFX_WARN("Can't Create Window Window no API defined");
		return nullptr;
#endif
	case RenderAPI::NVN:
#ifdef PLATFORM_SWITCH
		CE_GFX_INFO("Switch Window generated");
		return new NVNWindow(a_width, a_height, "CE | SWITCH | NVN");
#else
		CE_GFX_WARN("Can't Create Window NVN not implemented");
		return nullptr;
#endif
		break;
	}

	return nullptr;
}
