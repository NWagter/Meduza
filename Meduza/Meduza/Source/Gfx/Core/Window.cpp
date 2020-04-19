#include "mePch.h"

#include "Gfx/Core/Window.h"

#ifdef PLATFORM_WINDOWS

#include "Platform/Windows/WinWindow.h"

#endif

meduza::Window* meduza::Window::CreateNewWindow(int a_x, int a_y)
{

#ifdef PLATFORM_WINDOWS

	return new WinWindow(a_x, a_y, "Windows Window");
#else

	return nullptr;
#endif
}