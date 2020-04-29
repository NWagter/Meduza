#include "mePch.h"
#include "Core/Meduza.h"

#include "Platform/General/Renderer.h"
#include "Platform/General/Window.h"


meduza::Meduza::Meduza(API a_api)
{
	m_renderer = renderer::Renderer::CreateRenderer(a_api, math::Vec2(720,480));
}

meduza::Meduza::~Meduza()
{
	delete m_renderer;
}

void meduza::Meduza::EnableOptick()
{
	m_renderer->EnableOptick();
	MeduzaHelper::EnableOptick(true);
}

void meduza::Meduza::Submit(drawable::Drawable*)
{

}

void meduza::Meduza::Submit(std::vector<drawable::Drawable*>)
{

}

void meduza::Meduza::Clear(Colour a_colour)
{
	if (m_renderer != nullptr)
	{
		return m_renderer->Clear(a_colour);
	}
}

void meduza::Meduza::SwapBuffers()
{
	if (m_renderer != nullptr)
	{
		return m_renderer->SwapBuffers();
	}
}

void meduza::Meduza::Peek()
{
	if (m_renderer != nullptr)
	{
		return m_renderer->GetWindow().Peek();
	}
}

bool meduza::Meduza::IsWindowActive() const
{
	if (m_renderer != nullptr)
	{
		return m_renderer->GetWindow().GetActive();
	}

	return false;
}

std::string meduza::Meduza::GetWindowName()
{ 
	if (m_renderer != nullptr)
	{
		return m_renderer->GetWindow().GetTitle();
	}

	return "Unknown";
}


