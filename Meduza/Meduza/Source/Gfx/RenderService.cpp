#include "cepch.h"
#include "Gfx/RenderService.h"

#include "Gfx/RenderLayer.h"
#include "Gfx/Window.h"
#include "Core/Core.h"
#include "Gfx/Camera2D.h"
#include "Gfx/Camera.h"
#include "Gfx/IDrawable.h"

namespace ce
{
	void RenderService::OnCreate()
	{
		m_camera = new Camera2D();
		m_window = cr::Window::CreateNewWindow(cr::RenderLayer::GetUsedAPI(), 720, 480);
		m_renderer = cr::RenderLayer::CreateRenderLayer(*m_window);
	}

	void RenderService::OnDestroy()
	{
		delete m_camera;
		delete m_window;
		delete m_renderer;
	}

	void RenderService::Clear(float a_colour[4])
	{
		m_renderer->Clear(a_colour);
	}

	void RenderService::Peak()
	{
		m_window->Peak();
	}

	void RenderService::Update(float a_deltaTime)
	{
		m_renderer->Update(a_deltaTime);
	}

	void RenderService::Render()
	{
		m_renderer->Render();
	}

	void RenderService::Draw(cr::IDrawable* a_drawable)
	{
		m_renderer->Draw(a_drawable);
	}

	bool RenderService::IsWindowActive()
	{
		return m_window->IsActive();
	}

	glm::vec2 RenderService::GetSize()
	{
		CE_CORE_ASSERT(m_window);
		return m_window->GetSize();
	}

	cr::RenderLayer* RenderService::GetRenderLayer()
	{
		CE_CORE_ASSERT(m_renderer);
		return m_renderer;
	}
}