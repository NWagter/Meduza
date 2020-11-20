#include "MePCH.h"
#include "Utils/Timer.h"

#include "Core/Application.h"
#include "Core/Meduza.h"

#include "Platform/General/MeshLibrary.h"
#include "Platform/General/ShaderLibrary.h"
#include "Platform/General/TextureLibrary.h"

#include "ECS/EntityManager.h"
#include "Core/Components/RenderComponent.h"
#include "Core/Components/TransformComponent.h"
#include "Core/Components/CameraComponent.h"

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
    OnUpdate(a_dt);
}

bool Me::Application::Run()
{

    OnInitilized();

	Me::Texture texture = 0;
	Resources::TextureLibrary::CreateTexture("Assets/Textures/DefaultTex.png");
    Resources::TextureLibrary::CreateTexture("Assets/Textures/Checkboard.dds");

	Resources::ShaderLibrary::CreateShader("Assets/Shaders/Default_Shader.hlsl");
	Me::Shader shader = Resources::ShaderLibrary::CreateShader("Assets/Shaders/FlatColour_Shader.hlsl");

	if(shader == 0)
	{
		ME_CORE_LOG("No HLSL Shader");
		shader = Resources::ShaderLibrary::CreateShader("Assets/Shaders/Default_Shader.glsl");
        texture = Resources::TextureLibrary::GetTexture("Assets/Textures/DefaultTex.png");
		if(shader == 0)
		{
			ME_CORE_ASSERT_M(false, "No GLSL Shader!");
		}
	}

    if(texture == 0)
    {
        texture = Resources::TextureLibrary::GetTexture("Assets/Textures/DefaultTex.png");
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

    auto eManager = EntityManager::GetEntityManager();

    auto cC = new CameraComponent();
    cC->m_cameraType = CameraType::Orthographic;
    cC->m_near = 0;
    cC->m_far = 100;
    cC->m_size = Math::Vec2(CAM_WIDTH, CAM_HEIGHT);

    EntityID entCam = EntityManager::CreateEntity();
    eManager->AddComponent<CameraComponent>(entCam, cC);
    eManager->AddComponent<TransformComponent>(entCam);


    Timer<float> deltaTimer;
    float totalTime = 0.f;
    unsigned frameCount = 0;

    float fps;

    while(m_meduza->IsRunning())
    {
        const float deltaSeconds = deltaTimer.GetElapsedTime();
        m_meduza->Clear();
        m_meduza->Update(deltaSeconds);
        Application::OnUpdate(deltaSeconds);

        m_meduza->Present();

        totalTime += deltaSeconds;
        frameCount++;
        if (totalTime >= 1.f)
        {
            fps = float(frameCount) / totalTime;
            frameCount = 0;
            totalTime = 0.f;
            ME_CORE_LOG("FPS : %f \n", fps);
        }
    };

    OnClose();

    return true;
}

void Me::Application::SetName(std::string a_name)
{
    m_meduza->SetAppName(a_name);
}