#include "mePch.h"

#include "Core.h"
#include "Util/MeduzaHelper.h"

#include "Meduza.h"

#include "Platform/General/Renderer.h"
#include "Platform/General/Window.h"


meduza::Meduza::Meduza(API a_api)
{
	meduza::MeduzaHelper::ms_activeAPI = a_api;

	renderer::Renderer::RendererData* data = nullptr;

	data = renderer::Renderer::CreateRenderer(a_api, math::Vec2(720,480));

	if (data == nullptr)
	{
		ME_CORE_ASSERT_M(1, "Failed to generate Renderer!");
	}

	m_renderer = data->renderer;
	m_window = data->window;
}

meduza::Meduza::~Meduza()
{
	delete m_renderer;
}

void meduza::Meduza::EnableOptick()
{
	m_renderer->EnableOptick();
	MeduzaHelper::ms_optick = true;
}

void meduza::Meduza::EnableImGui()
{

	MeduzaHelper::ms_imGui = true;
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
		m_renderer->SwapBuffers();
		m_window->SwapBuffers();
	}
}

void meduza::Meduza::Peek()
{
	if (m_renderer != nullptr)
	{
		m_window->Peek();
	}
}

bool meduza::Meduza::IsWindowActive() const
{
	if (m_renderer != nullptr)
	{
		return m_window->GetActive();
	}

	return false;
}

std::string meduza::Meduza::GetWindowName()
{ 
	if (m_renderer != nullptr)
	{
		return m_window->GetTitle();
	}

	return "Unknown";
}


