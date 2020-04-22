#include "mePch.h"

#include "Platform/Windows/WinWindow.h"
#include "Platform/Windows/Gfx/OpenGL/ContextGL.h"

meduza::WinWindow::WinWindow(math::Vec2)
{
	m_windowActive = true;
	SetTitle("Meduza | Renderer | Windows");
}

meduza::WinWindow::~WinWindow()
{
}

void meduza::WinWindow::Peek()
{

}

void meduza::WinWindow::SwapBuffers()
{
	m_context->SwapBuffers();
}

void meduza::WinWindow::SetTitle(std::string a_title)
{
	m_title = a_title;
}
