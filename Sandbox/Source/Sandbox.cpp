#include "PCH.h"
#include "Sandbox.h"
#include "Meduza.h"

#include "MeduzaIncluder.h"

#define Run_ExampleScene 1
#define Run_Chess 0
#define Run_Physics 0

#include "Games/BaseGame.h"

#if Run_Chess
#include "Games/Chess/ChessGame.h"
#elif Run_Physics
#include "Games/Physics2D/Physics2D.h"
#elif Run_ExampleScene
#include "Games/Example/ExampleScene.h"
#endif

#include "Systems/CursorSystem.h"
#include "Systems/PlayerSystem.h"
#include "Systems/Rotator.h"
#include "Systems/MoveUpSystem.h"
#include "Systems/MoveForwardSystem.h"
#include "Components/RotateComponent.h"
#include "Components/UpComponent.h"
#include "Components/ForwardComponent.h"

Sandbox::Sandbox() : Me::Application(1280,720, Me::GFX_API::DX12)
{

#if Run_Chess
    new CursorSystem();
    new PlayerSystem();
    m_game = new Chess::ChessGame();
#elif Run_Physics
    new CursorSystem();
    new PlayerSystem();
    m_game = new Physics::Physics2D();
#elif Run_ExampleScene
    m_game = new ExampleScene();
#else

    m_game = new BaseGame();

    auto eManager = Me::EntityManager::GetEntityManager();

    auto cC = new Me::CameraComponent();
    cC->m_cameraType = Me::CameraType::Perspective;
    cC->m_near = 0.1f;
    cC->m_far = 1000;
    cC->m_size = Me::Event::EventSystem::GetEventSystem()->ScreenSize();

    EntityID entCam = Me::EntityManager::CreateEntity();
    eManager->AddComponent<Me::CameraComponent>(entCam, cC);
    eManager->AddComponent<Me::TransformComponent>(entCam);
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
Me::Application *Me::CreateApplication()
{
    return new Sandbox();
}