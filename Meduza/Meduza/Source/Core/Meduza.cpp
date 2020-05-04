#include "mePch.h"

#include "Core.h"
#include "Util/MeduzaHelper.h"

#include "Meduza.h"

#include "Platform/General/Gfx/Renderer.h"
#include "Platform/General/Window/Window.h"

#include "Platform/General/Gfx/ImGuiRenderer.h"
#include "Platform/General/Gfx/ShaderLibrary.h"

#ifdef WINDOWS
#include "Platform/Windows/Utils/FileSystem.h"
#endif // WINDOWS


meduza::Meduza::Meduza(API a_api)
{
	meduza::MeduzaHelper::ms_activeAPI = a_api;

	renderer::Renderer::RendererData* data = nullptr;
	data = renderer::Renderer::CreateRenderer(math::Vec2(720,480));

	if (data == nullptr)
	{
		ME_CORE_ASSERT_M(1, "Failed to generate Renderer!");
	}
	else
	{
		m_renderer = data->renderer;
		m_window = data->window;
	}

	ME_LOG("Window title = %s \n", GetWindowName().c_str());

	m_shaderLibrary = new ShaderLibrary();
	m_shaderLibrary->LoadShader("Data/Shaders/DefaultShader.glsl");

	delete data;
}

meduza::Meduza::~Meduza()
{
	if (m_imGuiRenderer != nullptr)
	{
		delete m_imGuiRenderer;
	}

	delete m_renderer;
	delete m_window;
}

void meduza::Meduza::EnableImGui()
{
	MeduzaHelper::ms_imGui = true;
	m_window->EnableImGui();
	m_imGuiRenderer = ImGuiRenderer::CreateRenderer(*m_renderer);
}

std::string meduza::Meduza::LoadShader(std::string a_path)
{
	m_shaderLibrary->LoadShader(a_path);
	return utils::FileSystem::GetFileName(a_path);
}

void meduza::Meduza::Submit(drawable::Drawable* a_drawable)
{
	if (m_renderer != nullptr)
	{
		m_renderer->Draw(a_drawable);
	}
}

void meduza::Meduza::Submit(std::vector<drawable::Drawable*> a_drawables)
{
	if (m_renderer != nullptr)
	{
		m_renderer->Submit(a_drawables);
	}
}

void meduza::Meduza::Clear(Colour a_colour)
{
	if (m_renderer != nullptr)
	{
		m_renderer->Clear(a_colour);

		if (MeduzaHelper::ms_imGui)
		{
			m_imGuiRenderer->Clear();
		}
	}
}

void meduza::Meduza::SwapBuffers()
{
	if (m_renderer != nullptr)
	{
		m_renderer->Render();

		if (MeduzaHelper::ms_imGui)
		{
			m_imGuiRenderer->Render();
		}
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


