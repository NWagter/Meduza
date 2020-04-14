#include "mePch.h"
#include "Core/Meduza.h"

#include "Core/Renderer.h"

meduza::Meduza::Meduza(API a_api)
{
	API api = a_api;

	m_renderer = renderer::Renderer::CreateRenderer(api);

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


