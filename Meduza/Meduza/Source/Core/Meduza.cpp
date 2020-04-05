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

}

void meduza::Meduza::Clear(float a_colour[])
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


