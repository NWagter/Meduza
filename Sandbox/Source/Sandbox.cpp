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
#include "Systems/Rotator.h"
#include "Systems/MoveUpSystem.h"
#include "Systems/MoveForwardSystem.h"
#include "Components/RotateComponent.h"
#include "Components/UpComponent.h"
#include "Components/ForwardComponent.h"

Sandbox::Sandbox()
{

#if Run_EmptyTest && PLATFORM_WINDOWS
    new CursorSystem();
    new PlayerSystem();
    m_game = new EmptyGame();
#elif Run_Chess && PLATFORM_WINDOWS
    new CursorSystem();
    new PlayerSystem();
    m_game = new Chess::ChessGame();
#elif Run_Physics
    new CursorSystem();
    new PlayerSystem();
    m_game = new Physics::Physics2D();
#else
    new Rotator();
    new MoveUpSystem();
    new MoveForwardSystem();
    m_game = new BaseGame();

    auto eManager = Me::EntityManager::GetEntityManager(); 
/*
    Me::Mesh mesh = Me::Resources::MeshLibrary::CreateMesh("Assets/Models/Suzanne/Suzanne.gltf");
    Me::Texture texture = Me::Resources::TextureLibrary::GetTexture("Assets/Models/Suzanne/Suzanne_BaseColor.png");
*/ 
    Me::Mesh mesh = Me::Resources::MeshLibrary::CreateMesh("Assets/Models/Avocado.glb");
    Me::Texture texture = Me::Resources::TextureLibrary::GetTexture("Assets/Models/Avocado.glb");

    Me::Shader shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/Lit_Shader.hlsl");
   
    if(shader == 0)
    {      
        shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/Lit_Shader.glsl");
    }

    EntityID entt = Me::EntityManager::CreateEntity();

    auto renderComp = new Me::RenderComponent();
    auto transComp = new Me::TransformComponent();
    auto rotComp = new RotateComponent();
    auto upComp = new UpComponent();
    auto forwardComp = new ForwardComponent();

    renderComp->m_colour = Me::Colours::WHITE;
    renderComp->m_shader = shader;
    renderComp->m_mesh = mesh;
    renderComp->m_texture = texture;

    Me::Math::Vec2 screenSize = GetScreenSize();

    
    //transComp->SetPosition(Me::Math::Vec3(screenSize.m_x * 0.5f,screenSize.m_y * 0.5f,32.0f));
    //transComp->SetUniformScale(1024.0f);
    
    transComp->SetPosition(Me::Math::Vec3(0.0f, 0.0f,10.0f));
    transComp->SetUniformScale(32.0f);
    
    transComp->SetRotationDegree(Me::Math::Vec3(0.0f,180.0f,0.0f));

    rotComp->m_rotateSpeed = 0.25f;
    upComp->m_upSpeed = 10.0f;
    forwardComp->m_forwardSpeed = 10.0f;

    eManager->AddComponent(entt, renderComp);
    eManager->AddComponent(entt, transComp);
    eManager->AddComponent(entt, rotComp);
    //eManager->AddComponent(entt, upComp);
    //eManager->AddComponent(entt, forwardComp);

    EntityID camEntt = Me::EntityManager::CreateEntity();

    auto camComp = new Me::CameraComponent();
    auto transCComp = new Me::TransformComponent();
    
    camComp->m_cameraType = Me::CameraType::Perspective;
    camComp->m_near = 0.1f;
    camComp->m_far = 1000;
    camComp->m_size = screenSize;

    eManager->AddComponent<Me::CameraComponent>(camEntt, camComp);
    eManager->AddComponent<Me::TransformComponent>(camEntt);

#endif

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