#include "mePch.h"
#include "Core/Meduza.h"

#include "Core/Renderer.h"

meduza::Meduza::Meduza()
{
	m_windowActive = true;

	API api = API::OpenGL;

	m_renderer = renderer::Renderer::CreateRenderer(api);
}

meduza::Meduza::~Meduza()
{
	delete m_renderer;
}

void meduza::Meduza::Clear(float a_colour[4])
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


