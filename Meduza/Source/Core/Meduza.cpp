#include "MePCH.h"
#include "Core/Meduza.h"

#include "ECS/EntityManager.h"

#include "Core/Components/TransformComponent.h"

#include "Core/Systems/RenderSystem.h"
#include "Core/Components/RenderComponent.h"

#include "Core/Systems/CameraSystem.h"
#include "Core/Components/CameraComponent.h"

#include "Core/Systems/EditorCameraSystem.h"
#include "AI/Systems/AgentMovementSystem.h"

#include "Core/Serialization/Serializer.h"

#include "Core/Components/PhysicsComponent.h"
#include "Physics/Systems/PhysicsSystem.h"


#include "Platform/General/Graphics/RenderLayer.h"

#include "Platform/General/MeshLibrary.h"
#include "Platform/General/ShaderLibrary.h"
#include "Platform/General/TextureLibrary.h"

#include "Platform/General/Events/EventSystem.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#include "Platform/General/Editor/EditorRenderer.h"
#elif PLATFORM_LINUX
#include "Platform/Linux/LinuxWindow.h"
#elif PLATFORM_APPLE
#include "Platform/MacOS/MacOsWindow.h"
#endif

#include "Core/Scripting/LuaScripting.h"
#include "Core/Scripting/ScriptSystem.h"

unsigned char Me::Meduza::ms_engineState = RUN_GAME;

Me::Meduza::Meduza(int a_w, int a_h, GFX_API a_api)
{
	m_isRunning = true;

#ifdef PLATFORM_WINDOWS
	m_window = new WindowsWindow(a_w, a_h, "Meduza | Windows");
	ms_engineState = RUN_EDITOR;
#elif PLATFORM_LINUX
	m_window = new LinuxWindow(a_w, a_h, "Meduza | Linux");
	ms_engineState = RUN_GAME;
#elif PLATFORM_APPLE
	m_window = new MacOsWindow(a_w, a_h, "Meduza | Apple");
#endif

	if(m_window != nullptr)
	{
		m_renderLayer = Renderer::RenderLayer::CreateRenderer(m_window, a_api);
#ifdef PLATFORM_WINDOWS
		m_editor = Editor::EditorRenderer::CreateEditor(m_renderLayer);
#endif
		if(m_renderLayer == nullptr)
		{			
			ME_CORE_ASSERT_M(false, "No Renderer Available!");
			m_window->Quit();
		}
	}

	Event::EventSystem::Create(m_window);
	Resources::MeshLibrary::CreateMeshLibrary(*m_renderLayer);
	Resources::ShaderLibrary::CreateShaderLibrary(*m_renderLayer);
	Resources::TextureLibrary::CreateTextureLibrary(*m_renderLayer);
	EntityManager::CreateEntityManager();
	m_serializer = new Serialization::Serializer();
	
	auto r = new RenderSystem(m_renderLayer);
	auto c = new CameraSystem(m_renderLayer);
	auto p = new Physics::PhysicsSystem();
	auto eC = new Editor::EditorCameraSystem();
	auto a = new AI::AgentMovementSystem();

	auto scripting = new Scripting::LuaScripting();
	auto sS = new Scripting::ScriptSystem();
}

Me::Meduza::~Meduza()
{
	Destroy();
}

void Me::Meduza::Clear()
{
	if(m_renderLayer != nullptr)
	{		
		m_renderLayer->Clear(Colours::CELESTIAL_BLUE);

#ifdef PLATFORM_WINDOWS
		if(m_editor != nullptr)
		{
			m_editor->Clear();
		}
#endif
		return;
	}

	m_isRunning = false;
}

void Me::Meduza::Update(float a_dt)
{
	if(m_window == nullptr)
	{
		m_isRunning = false;
		return;
	}
	
	m_window->Peek();
	EntityManager::GetEntityManager()->Update(a_dt);
		
	if (!m_window->IsActive())
	{
		m_isRunning = false;
	}
}

void Me::Meduza::Present()
{
	if(m_renderLayer != nullptr)
	{		
		m_renderLayer->Populate();

#ifdef PLATFORM_WINDOWS		
		if(m_editor != nullptr)
		{
			m_editor->Populate();
		}
#endif
		m_renderLayer->Present();
		return;
	}

	m_isRunning = false;
}

void Me::Meduza::SetAppName(std::string a_name)
{
	m_window->SetTitle(a_name);
}

Me::Math::Vec2 Me::Meduza::GetScreenSize()
{
	return m_window->GetSize();
}

void Me::Meduza::Destroy()
{
	Resources::TextureLibrary::Destroy();
	Resources::ShaderLibrary::Destroy();
	Resources::MeshLibrary::Destroy();
	Event::EventSystem::Destroy();

	if(m_window != nullptr)
	{
		delete m_window;
	}

	if(m_renderLayer != nullptr)
	{
		delete m_renderLayer;
	}	
	
	if(m_serializer != nullptr)
	{
		delete m_serializer;
	}
}