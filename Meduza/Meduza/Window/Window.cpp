#include "pch/pch.h"
#include "Window.h"

Window::Window(int a_width, int a_height, std::string a_title)
{
	m_width = a_width;
	m_height = a_height;
	m_title = a_title;
}

Window::~Window()
{
}

void Window::SetTitle(const std::string a_newTitle)
{
	m_title = a_newTitle;
}

bool Window::IsWindowActive()
{
	return 	m_windowIsActive;
}
