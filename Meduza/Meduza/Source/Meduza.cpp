#include "mePch.h"

#include "Core.h"
#include "Platform/General/Utils/MeduzaHelper.h"

#include "Meduza.h"
#include "Event/EventSystem.h"

#include "Platform/General/Gfx/Renderer.h"
#include "Platform/General/Window/Window.h"

#include "Platform/General/Gfx/ImGuiRenderer.h"
#include "Platform/General/Gfx/ShaderLibrary.h"
#include "Platform/General/Gfx/TextureLibrary.h"
#include "Platform/General/Gfx/MaterialLibrary.h"

#include "Camera/Camera.h"

#ifdef WINDOWS
#include "Platform/Windows/Utils/FileSystem.h"
#endif // WINDOWS

#include "Editor/EditorMenu.h"

#include "Renderable/Renderable.h"
#include "Scene/Scene.h"

meduza::Meduza::Meduza(API a_api)
{
	SetupRenderer(a_api);
}


meduza::Meduza::Meduza(API a_api, std::string a_title)
{
	SetupRenderer(a_api);
	SetWindowTitle(a_title);
	
}

meduza::Meduza::~Meduza()
{
	if (m_imGuiRenderer != nullptr)
	{
		delete m_editorMenu;
		delete m_imGuiRenderer;
	}

	delete m_materialLibrary;
	delete m_shaderLibrary;
	delete m_textureLibrary;
	delete m_renderer;
	delete m_window;
	delete m_camera;
	delete m_eventSystem;
}

meduza::API meduza::Meduza::GetCurrentAPI() const
{
	return meduza::MeduzaHelper::ms_activeAPI;
}

void meduza::Meduza::SetupRenderer(meduza::API a_api)
{
	meduza::MeduzaHelper::ms_activeAPI = a_api;

	renderer::Renderer::RendererData* data = nullptr;
	data = renderer::Renderer::CreateRenderer(math::Vec2(1080, 720));

	m_eventSystem = new EventSystem();

	if (data == nullptr)
	{
		ME_CORE_ASSERT_M(0, "Failed to generate Renderer!");
	}
	else
	{
		m_renderer = data->renderer;
		m_window = data->window;
		m_window->SetEventSystem(*m_eventSystem);
	}

	ME_LOG("Window title = %s \n", GetWindowName().c_str());

	m_shaderLibrary = new ShaderLibrary();
	m_materialLibrary = new MaterialLibrary();
	m_textureLibrary = new TextureLibrary();

	m_camera = Camera::CreateCamera(CameraPerspective::Orthographic, m_window->GetSize(), math::Vec2(-1, 1));

	delete data;

}

void meduza::Meduza::SetupRenderer(math::Vec2 a_size)
{
	renderer::Renderer::RendererData* data = nullptr;

	delete m_window;
	m_window = nullptr;
	data = renderer::Renderer::CreateRenderer(a_size);
	

	if (m_eventSystem == nullptr)
	{
		m_eventSystem = new EventSystem();
	}

	if (data == nullptr)
	{
		ME_CORE_ASSERT_M(0, "Failed to generate Renderer!");
	}
	else
	{
		m_renderer = data->renderer;
		m_window = data->window;
		m_window->SetEventSystem(*m_eventSystem);
	}

	ME_LOG("Window title = %s \n", GetWindowName().c_str());

	if (MeduzaHelper::ms_imGui)
	{
		m_window->EnableImGui();
		m_imGuiRenderer = ImGuiRenderer::CreateRenderer(*m_renderer);
		m_editorMenu = new editor::EditorMenu(*m_renderer, *m_window);
	}

	m_reload = true;
	m_shaderLibrary->Reload();
	m_materialLibrary->Reload();
	m_textureLibrary->Reload();

	delete data;
}

void meduza::Meduza::EnableImGui()
{
	MeduzaHelper::ms_imGui = true;
	m_window->EnableImGui();
	m_imGuiRenderer = ImGuiRenderer::CreateRenderer(*m_renderer);
	m_editorMenu = new editor::EditorMenu(*m_renderer, *m_window);
}

void meduza::Meduza::ChangeApi(meduza::API a_newApi)
{
	if (a_newApi == MeduzaHelper::ms_activeAPI)
	{
		return;
	}

	m_apiChange = true;

	MeduzaHelper::ms_activeAPI = a_newApi;
}

std::string meduza::Meduza::LoadShader(std::string a_path) const
{
	m_shaderLibrary->LoadShader(a_path);
	return utils::FileSystem::GetFileName(a_path);
}

meduza::Shader& meduza::Meduza::GetShader(std::string a_path) const
{
	return *m_shaderLibrary->LoadShader(a_path);
}

std::string meduza::Meduza::LoadTexture(std::string a_path) const
{
	m_textureLibrary->LoadTexture(a_path);
	return utils::FileSystem::GetFileName(a_path);
}
meduza::Texture& meduza::Meduza::GetTexture(std::string a_path) const
{	
	return *m_textureLibrary->LoadTexture(a_path);
}

meduza::Material& meduza::Meduza::CreateMaterial(Shader* a_shader, std::string a_name)
{
	return *m_materialLibrary->CreateMaterial(*a_shader, a_name);
}

meduza::Material& meduza::Meduza::GetMaterial(std::string a_name)
{
	return *m_materialLibrary->GetMaterial(utils::GetHashedID(a_name));
}

meduza::Material& meduza::Meduza::GetMaterial(unsigned int a_id)
{
	return *m_materialLibrary->GetMaterial(a_id);
}


void meduza::Meduza::SetMaterialParameter(meduza::Material& a_material, std::string a_name, float a_data[])
{
	a_material.SetData(a_name, a_data);
}

void meduza::Meduza::SetMaterialParameter(meduza::Material& a_material, std::string a_name, meduza::Texture& a_texture)
{
	unsigned int data[] = { unsigned int(a_texture.GetId()) };

	a_material.SetData(a_name, data);
}

void meduza::Meduza::SetNewCamera(CameraPerspective a_perspective, math::Vec2 a_size, math::Vec2 a_distance)
{
	delete m_camera;
	m_camera = Camera::CreateCamera(a_perspective, a_size, a_distance);
}

void meduza::Meduza::SetView(math::Vec2 a_size, math::Vec2 a_distance)
{	
	if (m_camera == nullptr)
	{
		return;
	}

	if (a_size.m_x > 0 || a_size.m_y > 0)
	{
		m_camera->SetProjection(a_size, a_distance);

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

void meduza::Meduza::SetSolidColour(Colour a_colour)
{
	if (m_camera != nullptr)
	{
		m_camera->SetColour(a_colour);
	}
}

void meduza::Meduza::SetSolidColour(float a_colour[4])
{
	if (m_camera != nullptr)
	{
		m_camera->SetColour(Colour(a_colour));
	}
}

void meduza::Meduza::Submit(Renderable& a_renderable)
{
	if (m_renderer != nullptr && !MeduzaHelper::ms_minimized)
	{
		if (m_reload)
		{
			a_renderable.Reload();
		}

		m_renderer->Submit(a_renderable);
	}
}

void meduza::Meduza::Submit(Scene& a_scene)
{
	if (m_renderer != nullptr && !MeduzaHelper::ms_minimized)
	{
		if (m_reload)
		{
			a_scene.Reload();
		}

		m_renderer->Submit(a_scene);
	}
}

void meduza::Meduza::Clear()
{
	if (m_renderer != nullptr && !MeduzaHelper::ms_minimized)
	{
		m_renderer->Clear(m_camera->GetSolidColour());

		if (MeduzaHelper::ms_imGui)
		{
			m_imGuiRenderer->Clear();
		}
	}

	if (m_imGuiRenderer != nullptr && static_cast<editor::EditorMenu*>(m_editorMenu)->GetChangeAPI())
	{
		m_apiChange = true;
	}

	if (m_apiChange)
	{
		m_apiChange = false;
		math::Vec2 size = m_window->GetSize();
		if (m_imGuiRenderer != nullptr)
		{
			delete m_editorMenu;
			m_editorMenu = nullptr;
			delete m_imGuiRenderer;
			m_imGuiRenderer = nullptr;
		}
		delete m_renderer;
		m_renderer = nullptr;

		SetupRenderer(size);
		Clear();
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

		if (m_reload)
		{
			m_reload = false;
		}
	}
}

void meduza::Meduza::Update(const float a_dt)
{
	if (MeduzaHelper::ms_imGui)
	{
		m_editorMenu->Update(a_dt);
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

void meduza::Meduza::SetWindowTitle(std::string a_title)
{
	m_window->SetTitle(a_title);
}

meduza::math::Vec2 meduza::Meduza::GetWindowSize() const
{
	return m_window->GetSize();
}


