#include "PCH.h"
#include "Sandbox.h"
#include "Meduza.h"

#include "MeduzaIncluder.h"

#define Run_EmptyTest 0
#define Run_Chess 0
#define Run_Physics 0

#include "Games/BaseGame.h"

#if Run_EmptyTest
#include "Games/Empty/EmptyGame.h"
#elif Run_Chess
#include "Games/Chess/ChessGame.h"
#elif Run_Physics
#include "Games/Physics2D/Physics2D.h"
#endif

#include "Systems/CursorSystem.h"
#include "Systems/PlayerSystem.h"

Sandbox::Sandbox()
{

#if Run_EmptyTest && PLATFORM_WINDOWS
    new CursorSystem();
    new PlayerSystem();
    m_game = new EmptyGame();
#elif Run_Chess
    new CursorSystem();
    new PlayerSystem();
    m_game = new Chess::ChessGame();
#elif Run_Physics
    new CursorSystem();
    new PlayerSystem();
    m_game = new Physics::Physics2D();
#endif

    m_game = new BaseGame();

    auto eManager = Me::EntityManager::GetEntityManager(); 

    Me::Shader mesh = Me::Resources::MeshLibrary::GetMeshIndex(Me::Primitives::Quad);
    Me::Shader shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/UnlitColour_Shader.hlsl");
   
    if(shader == 0)
    {      
        shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/UnlitColour_Shader.glsl");
    }

    EntityID entt = Me::EntityManager::CreateEntity();

    auto renderComp = new Me::RenderComponent();
    auto transComp = new Me::TransformComponent();

    renderComp->m_colour = Me::Colours::RED;
    renderComp->m_shader = shader;
    renderComp->m_mesh = mesh;

    transComp->SetPosition(Me::Math::Vec3(0,0,0));
    transComp->SetUniformScale(128);

    eManager->AddComponent(entt, renderComp);
    eManager->AddComponent(entt, transComp);

    EntityID camEntt = Me::EntityManager::CreateEntity();

    auto camComp = new Me::CameraComponent();
    auto transCComp = new Me::TransformComponent();
    
    camComp->m_cameraType = Me::CameraType::Orthographic;
    camComp->m_near = 0.0f;
    camComp->m_far = 100;
    camComp->m_size = GetScreenSize();

    eManager->AddComponent(camEntt, camComp);
    eManager->AddComponent(camEntt, transCComp);

    SetName(m_game->GetGameName() + " | Meduza");

}

Sandbox::~Sandbox()
{

}


void Sandbox::OnUpdate(float a_dt)
{   
    m_game->UpdateGame(a_dt);
}

void Sandbox::OnInitilized()
{
    ME_GAME_LOG("Game Initilzed \n");

    m_game->InitGame();
}

void Sandbox::OnClose()
{
    ME_GAME_LOG("Game Closed \n");
}

//Create the game "Application"
Me::Application* Me::CreateApplication()
{
	return new Sandbox();
}