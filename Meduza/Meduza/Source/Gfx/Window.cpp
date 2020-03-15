#include "mePch.h"
#include "Gfx/Window.h"

#include "Gfx/RenderLayer.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/WinWindow.h"
#endif

mr::Window* mr::Window::NewWindow(int a_w, int a_h,RenderAPI a_api)
{
	switch (a_api)
	{
	case mr::RenderAPI::None:
		break;
	case mr::RenderAPI::DX12:
#ifdef PLATFORM_WINDOWS
		return new WinWindow(a_w, a_h, "Meduza | WNDOWS | DX12");
#endif
		break;
	default:
		break;
	}

	return nullptr;
}
