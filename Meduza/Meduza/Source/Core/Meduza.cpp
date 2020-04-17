#include "mePch.h"
#include "Core/Meduza.h"

#include "Platform/Windows/WinWindow.h"
#include "Core/Renderer.h"

meduza::Meduza::Meduza(API a_api)
{
	API api = a_api;

	m_window = Window::CreateNewWindow(720,480);
	m_renderer = renderer::Renderer::CreateRenderer(api, *m_window);

	

	if (m_renderer != nullptr)
	{
		m_windowActive = true;
	}
}

meduza::Meduza::~Meduza()
{
	if (m_renderer != nullptr)
	{
		delete m_renderer;
	}

	delete m_window;
}

void meduza::Meduza::Clear(Colour a_colour)
{
	if (m_renderer != nullptr)
	{
		m_renderer->Clear(a_colour);
	}
}

void meduza::Meduza::Render()
{
	if (m_renderer != nullptr)
	{
		m_renderer->Render();
	}
}

void meduza::Meduza::Peek()
{
	m_window->Peek();
}

bool meduza::Meduza::IsWindowActive() const
{
	return m_window->WindowActive();
}

std::string meduza::Meduza::GetWindowName()
{ 
	if (m_window != nullptr)
	{
		return m_window->GetTitle();
	}
	else
	{
		return "Unknown";
	}
}


