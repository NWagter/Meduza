#include "mePch.h"

#include "Core.h"
#include "Util/MeduzaHelper.h"

#include "Meduza.h"
#include "Event/EventSystem.h"

#include "Platform/General/Gfx/Renderer.h"
#include "Platform/General/Window/Window.h"

#include "Platform/General/Gfx/ImGuiRenderer.h"
#include "Platform/General/Gfx/ShaderLibrary.h"
#include "Platform/General/Gfx/TextureLibrary.h"

#include "Camera/Camera.h"

#ifdef WINDOWS
#include "Platform/Windows/Utils/FileSystem.h"
#endif // WINDOWS

meduza::Meduza::Meduza(API a_api)
{
	meduza::MeduzaHelper::ms_activeAPI = a_api;

	renderer::Renderer::RendererData* data = nullptr;
	data = renderer::Renderer::CreateRenderer(math::Vec2(720,480));
	m_eventSystem = new EventSystem();

	if (data == nullptr)
	{
		ME_CORE_ASSERT_M(1, "Failed to generate Renderer!");
	}
	else
	{
		m_renderer = data->renderer;
		m_window = data->window;
		m_window->SetEventSystem(*m_eventSystem);
	}

	ME_LOG("Window title = %s \n", GetWindowName().c_str());

	m_shaderLibrary = new ShaderLibrary();
	m_shaderLibrary->LoadShader("Data/Shaders/DefaultShader.glsl");
	m_textureLibrary = new TextureLibrary();

	float width = m_window->GetSize().m_x / 2;
	float height = m_window->GetSize().m_y / 2;

	m_camera = Camera::CreateCamera(CameraPerspective::Orthographic, math::Vec4(-width, width,-height, height), math::Vec2(-1,1));

	delete data;
}

meduza::Meduza::~Meduza()
{
	if (m_imGuiRenderer != nullptr)
	{
		delete m_imGuiRenderer;
	}

	delete m_shaderLibrary;
	delete m_textureLibrary;
	delete m_renderer;
	delete m_window;
	delete m_camera;
	delete m_eventSystem;
}

void meduza::Meduza::EnableImGui()
{
	MeduzaHelper::ms_imGui = true;
	m_window->EnableImGui();
	m_imGuiRenderer = ImGuiRenderer::CreateRenderer(*m_renderer);
}

std::string meduza::Meduza::LoadShader(std::string a_path) const
{
	m_shaderLibrary->LoadShader(a_path);
	return utils::FileSystem::GetFileName(a_path);
}

std::string meduza::Meduza::LoadTexture(std::string a_path) const
{
	m_textureLibrary->LoadTexture(a_path);
	return utils::FileSystem::GetFileName(a_path);
}

void meduza::Meduza::SetNewCamera(CameraPerspective a_perspective, math::Vec4 a_frustrum, math::Vec2 a_distance)
{
	delete m_camera;
	m_camera = Camera::CreateCamera(a_perspective, a_frustrum, a_distance);
}

void meduza::Meduza::SetView(math::Vec2 a_size, math::Vec2 a_distance)
{	
	if (m_camera == nullptr)
	{
		return;
	}

	if (a_size.m_x > 0 || a_size.m_y > 0)
	{
		math::Vec4 frustrum(-a_size.m_x / 2, a_size.m_x / 2, -a_size.m_y / 2, a_size.m_y / 2);
		m_camera->SetProjection(frustrum, a_distance);

		if (MeduzaHelper::ms_minimized)
		{
			MeduzaHelper::ms_minimized = false;
		}
		return;
	}

	MeduzaHelper::ms_minimized = true;
}

void meduza::Meduza::SetCamEye(math::Vec3 a_pos)
{
	if (m_camera != nullptr && !MeduzaHelper::ms_minimized)
	{
		m_camera->SetEye(a_pos);
	}
}

void meduza::Meduza::Submit(drawable::Drawable* a_drawable)
{
	if (m_renderer != nullptr && !MeduzaHelper::ms_minimized)
	{
		m_renderer->Draw(a_drawable);
	}
}

void meduza::Meduza::Submit(std::vector<drawable::Drawable*> a_drawables)
{
	if (m_renderer != nullptr && !MeduzaHelper::ms_minimized)
	{
		m_renderer->Submit(a_drawables);
	}
}

void meduza::Meduza::Clear(Colour a_colour)
{
	if (m_renderer != nullptr && !MeduzaHelper::ms_minimized)
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
	if (m_renderer != nullptr && !MeduzaHelper::ms_minimized)
	{
		m_renderer->Render(*m_camera);

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

std::string meduza::Meduza::GetWindowName() const
{ 
	if (m_renderer != nullptr)
	{
		return m_window->GetTitle();
	}

	return "Unknown";
}

meduza::math::Vec2 meduza::Meduza::GetWindowSize() const
{
	return m_window->GetSize();
}


