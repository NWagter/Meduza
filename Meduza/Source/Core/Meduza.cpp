#include "MePCH.h"

#include "Core/Meduza.h"
#include "Core/ThreadPool.h"

#include "ECS/EntityManager.h"

#include "Core/Serialization/Serializer.h"
#include "Core/Systems/SystemInitializer.h"

#include "Platform/General/Graphics/RenderLayer.h"

#include "Core/Project/ProjectManager.h"
#include "Platform/General/ResourceLibrary.h"

#include "Platform/General/Events/EventSystem.h"
#include "Utils/MeduzaDebug.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#include "Platform/General/Editor/EditorRenderer.h"
#elif PLATFORM_LINUX
#include "Platform/Linux/LinuxWindow.h"
#elif PLATFORM_APPLE
#include "Platform/MacOS/MacOsWindow.h"
#endif

#include "Core/Scripting/ScriptConfig.h"
#include "Core/Scripting/LuaScripting.h"
#include "Core/Scripting/ScriptSystem.h"

unsigned char Me::Meduza::ms_engineState = RUN_GAME;

Me::Meduza::Meduza(int a_width, int a_height, GFX_API a_api, std::string a_startingProject)
	:
	m_renderLayer(nullptr),
	m_serializer(nullptr),
	m_systemInitializer(nullptr),
	m_luaScripting(nullptr),
	m_window(nullptr)
#ifdef PLATFORM_WINDOWS
	,
	m_editor(nullptr)
#endif
{
	m_isRunning = true;
	
#ifdef PLATFORM_WINDOWS
	m_window = new WindowsWindow(a_width, a_height, "Meduza | Windows");
	ms_engineState = RUN_EDITOR;
#elif PLATFORM_LINUX
	m_window = new LinuxWindow(a_width, a_height, "Meduza | Linux");
	ms_engineState = RUN_GAME;
#elif PLATFORM_APPLE
	m_window = new MacOsWindow(a_width, a_height, "Meduza | Apple");
#endif

	if(m_window != nullptr)
	{
		m_renderLayer = Renderer::RenderLayer::CreateRenderer(m_window, a_api);
	}

	if (m_renderLayer == nullptr)
	{
		ME_CORE_ASSERT_M(false, "No Renderer Available!");
		m_window->Quit();
		return;
	}

	Threading::ThreadPool::CreateThreadPool();

	Resources::ResourceLibrary::CreateResourceLibrary();
	Event::EventSystem::Create(m_window);
	m_meduzaDebugger = Debug::MeduzaDebug::CreateDebugger(*m_renderLayer);

	EntityManager::CreateEntityManager();
	m_serializer = new Serialization::Serializer();
	m_systemInitializer = new SystemInitializer(*m_renderLayer);
	m_luaScripting = new Scripting::LuaScripting();

	m_scriptConfig = Scripting::ScriptConfig::CreateScriptConfig();

	m_projectManager = Project::ProjectManager::CreateProjectManager();

	if (!a_startingProject.empty())
	{
		m_projectManager->LoadProject(a_startingProject);
	}

#ifdef PLATFORM_WINDOWS
#ifdef EDITOR
	m_editor = Editor::EditorRenderer::CreateEditor(m_renderLayer);
#endif
#endif

#ifndef EDITOR
	std::string startingProject = a_startingProject.empty() ? "Projects/MeduzaTests/Config/.ProjectMeduzaTests.mec" : a_startingProject;
	ms_engineState = RUN_GAME;
	m_projectManager->LoadProject(startingProject);
#endif
}

Me::Meduza::~Meduza()
{
	Destroy();
}

void Me::Meduza::Update(float a_dt)
{
	if(m_window == nullptr)
	{
		m_isRunning = false;
		return;
	}
	
	m_window->Peek();
	Resources::ResourceLibrary::GetInstance()->LoadNewResources();
	EntityManager::GetEntityManager()->Update(a_dt);
		
#ifdef PLATFORM_WINDOWS
	#ifdef EDITOR		
		if (m_editor != nullptr)
		{
			m_editor->Update(a_dt);
		}
	#endif
#endif

	if (!m_window->IsActive())
	{
		m_isRunning = false;
	}
}

void Me::Meduza::Render()
{
	if(m_renderLayer != nullptr)
	{		
		m_renderLayer->Populate();

#ifdef PLATFORM_WINDOWS
	#ifdef EDITOR		
		if(m_editor != nullptr)
		{
			m_editor->Clear();
			m_editor->Populate();
		}
	#endif
#endif
		m_renderLayer->Present();
		m_renderLayer->Clear(Colours::CELESTIAL_BLUE);
		return;
	}

	m_isRunning = false;
}

void Me::Meduza::SetAppName(std::string a_appName)
{
	m_window->SetTitle(a_appName);
}

Me::Math::Vector2 Me::Meduza::GetScreenSize()
{
	return m_window->GetSize();
}

void Me::Meduza::Destroy()
{
	Resources::ResourceLibrary::Destroy();
	Event::EventSystem::Destroy();
	Serialization::Serializer::DestroySerializer();

	if(m_window != nullptr)
	{
		delete m_window;
	}

	if(m_renderLayer != nullptr)
	{
		delete m_renderLayer;
	}	

#ifdef PLATFORM_WINDOWS
	if(m_editor != nullptr)
	{
		delete m_editor;
	}
#endif
	if (m_luaScripting != nullptr)
	{
		delete m_luaScripting;
	}

	if(m_systemInitializer != nullptr)
	{
		delete m_systemInitializer;
	}

	delete m_meduzaDebugger;
	delete m_projectManager;
	delete m_scriptConfig;

	EntityManager::DestroyEntityManager();
	Threading::ThreadPool::DestroyThreadPool();
}

