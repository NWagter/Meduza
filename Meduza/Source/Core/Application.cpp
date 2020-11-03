#include "MePCH.h"

#include "Core/Application.h"
#include "Core/Meduza.h"

#include "Platform/General/MeshLibrary.h"
#include "Platform/General/ShaderLibrary.h"
#include "Platform/General/TextureLibrary.h"

Me::Application::Application()
{
    m_meduza = new Meduza();
}

Me::Application::~Application()
{
    delete m_meduza;
}

void Me::Application::OnUpdate(float a_dt)
{
    m_meduza->Submit(m_renderable);

    
    OnUpdate(a_dt);
}

bool Me::Application::Run()
{

    OnInitilized();

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

    while(m_meduza->IsRunning())
    {
        m_meduza->Clear();
        m_meduza->Update();
        Application::OnUpdate(0);

        m_meduza->Present();
    };

    OnClose();

    return true;
}