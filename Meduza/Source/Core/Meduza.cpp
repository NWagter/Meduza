#include "MePCH.h"
#include "Core/Meduza.h"

#include "ECS/EntityManager.h"

#include "Core/Components/TransformComponent.h"

#include "Core/Systems/RenderSystem.h"
#include "Core/Components/RenderComponent.h"

#include "Core/Systems/CameraSystem.h"
#include "Core/Components/CameraComponent.h"
#include "Core/Components/TransformComponent.h"

#include "Platform/General/Graphics/RenderLayer.h"

#include "Platform/General/MeshLibrary.h"
#include "Platform/General/ShaderLibrary.h"
#include "Platform/General/TextureLibrary.h"

#include "Platform/General/Events/EventSystem.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#elif PLATFORM_LINUX
#include "Platform/Linux/LinuxWindow.h"
#elif PLATFORM_APPLE
#include "Platform/MacOS/MacOsWindow.h"
#endif


Me::Meduza::Meduza(int a_w, int a_h)
{
	m_isRunning = true;

#ifdef PLATFORM_WINDOWS
	m_window = new WindowsWindow(a_w, a_h, "Meduza | Windows");
#elif PLATFORM_LINUX
	m_window = new LinuxWindow(a_w, a_h, "Meduza | Linux");
#elif PLATFORM_APPLE
	m_window = new MacOsWindow(a_w, a_h, "Meduza | Apple");
#endif

	if(m_window != nullptr)
	{
		m_renderLayer = Renderer::RenderLayer::CreateRenderer(m_window);

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
	
	auto r = new RenderSystem(m_renderLayer);
	auto c = new CameraSystem(m_renderLayer);

	CreatePrimitives();
}

Me::Meduza::~Meduza()
{
	Destroy();
}

void Me::Meduza::Clear()
{
	if(m_renderLayer != nullptr)
	{		
		m_renderLayer->Clear(Colours::ROYAL_PURPLE);
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
}

void Me::Meduza::CreatePrimitives()
{
	// Create Quad!
	std::vector<Vertex> quadVertices = 
	{
        Vertex(-0.5f,  0.5f, 0.0f, 0.0f, 0.0f), // top left,
        Vertex(0.5f,  0.5f, 0.0f, 1.0f, 0.0f) ,  // top right
        Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f), // bottom left 
        Vertex(0.5f, -0.5f, 0.0f, 1.0f, 1.0f), // bottom right 
    };

	std::vector<uint16_t> quadIndices = 
	{
        0, 1, 3,
        0, 3, 2
    };

	uint16_t quadId = static_cast<uint16_t>(Primitives::Quad);
	Resources::MeshLibrary::CreateMesh(quadId, quadVertices, quadIndices);

	// Create Cube!
	std::vector<Vertex> cubeVertices = 
	{
		// Front
		Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 0.0f),
		Vertex(0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
		Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
		Vertex(0.5f, 0.5f, -0.5f, 0.0f, 0.0f),
		// Right
		Vertex(0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
		Vertex(0.5f, 0.5f, 0.5f, 0.0f, 0.0f),
		Vertex(0.5f, -0.5f, 0.5f, 0.0f, 0.0f),
		Vertex(0.5f, 0.5f, -0.5f, 0.0f, 0.0f),
		// Left
		Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f),
		Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
		Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f),
		Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 0.0f),
		// Back
		Vertex(0.5f, 0.5f, 0.5f, 0.0f, 0.0f),
		Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f),
		Vertex(0.5f, -0.5f, 0.5f, 0.0f, 0.0f),
		Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f),
		// Top
		Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 0.0f),
		Vertex(0.5f, 0.5f, 0.5f, 0.0f, 0.0f),
		Vertex(0.5f, 0.5f, -0.5f, 0.0f, 0.0f),
		Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f),
		// Bot
		Vertex(0.5f, -0.5f, 0.5f, 0.0f, 0.0f),
		Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
		Vertex(0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
		Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f)
    };

	std::vector<uint16_t> cubeIndices = 
	{
		// front face
		0, 1, 2, // first triangle
		0, 3, 1, // second triangle

		// left face
		4, 5, 6, // first triangle
		4, 7, 5, // second triangle

		// right face
		8, 9, 10, // first triangle
		8, 11, 9, // second triangle

		// back face
		12, 13, 14, // first triangle
		12, 15, 13, // second triangle

		// top face
		16, 17, 18, // first triangle
		16, 19, 17, // second triangle

		// bottom face
		20, 21, 22, // first triangle
		20, 23, 21, // second triangle
    };
	
	uint16_t cubeId = static_cast<uint16_t>(Primitives::Cube);
	Resources::MeshLibrary::CreateMesh(cubeId, cubeVertices, cubeIndices);
}