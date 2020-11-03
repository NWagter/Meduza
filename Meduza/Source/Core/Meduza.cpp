#include "MePCH.h"
#include "Core/Meduza.h"

#include "Platform/General/Graphics/RenderLayer.h"

#include "Platform/General/MeshLibrary.h"
#include "Platform/General/ShaderLibrary.h"
#include "Platform/General/TextureLibrary.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#elif PLATFORM_LINUX
#include "Platform/Linux/LinuxWindow.h"
#elif PLATFORM_APPLE
#include "Platform/MacOS/MacOsWindow.h"
#endif


Me::Meduza::Meduza()
{
	m_isRunning = true;

#ifdef PLATFORM_WINDOWS
	m_window = new WindowsWindow(720, 680, "Meduza | Windows");
#elif PLATFORM_LINUX
	m_window = new LinuxWindow(720, 680, "Meduza | Linux");
#elif PLATFORM_APPLE
	m_window = new MacOsWindow(720, 680, "Meduza | Apple");
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

	Resources::MeshLibrary::CreateMeshLibrary(*m_renderLayer);
	Resources::ShaderLibrary::CreateShaderLibrary(*m_renderLayer);
	Resources::TextureLibrary::CreateTextureLibrary(*m_renderLayer);

	Me::Texture texture = Resources::TextureLibrary::CreateTexture("Assets/Textures/Checkboard.dds");
	Resources::TextureLibrary::CreateTexture("Assets/Textures/DefaultTex.png");

	Me::Shader shader = Resources::ShaderLibrary::CreateShader("Assets/Shaders/Default_Shader.hlsl");
	if(shader == 0)
	{
		ME_CORE_LOG("No HLSL Shader");
		shader = Resources::ShaderLibrary::CreateShader("Assets/Shaders/Default_Shader.glsl");

		if(shader == 0)
		{
			ME_CORE_ASSERT_M(false, "No GLSL Shader!");
		}
	}
	// Create Quad!
	std::vector<Vertex> vertices = 
	{
        Vertex(-0.5f,  0.5f, 0.0f, 0.0f, 0.0f), // top left,
        Vertex(0.5f,  0.5f, 0.0f, 1.0f, 0.0f) ,  // top right
        Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f), // bottom left 
        Vertex(0.5f, -0.5f, 0.0f, 1.0f, 1.0f), // bottom right 
    };

	std::vector<uint16_t> indices = 
	{
        0, 1, 3,
        0, 3, 2
    };
	uint16_t quadId = static_cast<uint16_t>(Primitives::Quad);
	Resources::MeshLibrary::CreateMesh(quadId, vertices, indices);

	m_renderable = new Renderable();
	m_renderable->m_mesh = quadId;
	m_renderable->m_shader = shader;
	m_renderable->m_texture = texture;
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

void Me::Meduza::Update()
{
	if(m_window == nullptr)
	{
		m_isRunning = false;
		return;
	}
	
	m_window->Peek();
		
	if (!m_window->IsActive())
	{
		m_isRunning = false;
	}
}

void Me::Meduza::Present()
{
	if(m_renderLayer != nullptr)
	{		
		m_renderLayer->Submit(*m_renderable);
		m_renderLayer->Present();
		return;
	}

	m_isRunning = false;
}

void Me::Meduza::Destroy()
{
	Resources::TextureLibrary::Destroy();
	Resources::ShaderLibrary::Destroy();
	Resources::MeshLibrary::Destroy();

	if(m_window != nullptr)
	{
		delete m_window;
	}

	if(m_renderLayer != nullptr)
	{
		delete m_renderLayer;
	}
}
