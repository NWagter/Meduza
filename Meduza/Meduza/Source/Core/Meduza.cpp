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
}

void meduza::Meduza::Submit(drawable::Drawable*)
{

}

void meduza::Meduza::Submit(std::vector<drawable::Drawable*>)
{

}

void meduza::Meduza::Clear(Colour)
{

}

void meduza::Meduza::Render()
{

}

void meduza::Meduza::Peek()
{

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


