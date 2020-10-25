#include "MePCH.h"
#include "Platform/General/Window.h"

Me::Window::Window(int a_w, int a_h, const char* a_title)
{
	m_width = a_w;
	m_height = a_h;
	m_title = a_title;

	m_active = false;
}

Me::Window::~Window()
{

}

