#include "MePCH.h"
#include "Platform/General/Window.h"

#include "Platform/General/Events/EventSystem.h"

Me::Window::Window(int const a_w, int const a_h, const char* a_title)
{
	m_size = Math::Vector2(a_w, a_h);
	m_title = a_title;

	m_active = false;
}

Me::Window::~Window()
{

}

void Me::Window::SetEventSystem(Event::EventSystem* a_system) 
{
	m_eventSystem = a_system;
	m_eventSystem->m_screenSize = m_size;
}
