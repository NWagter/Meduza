#include "PCH.h"
#include "Game.h"
#include "Meduza.h"

#include "MeduzaIncluder.h"

#include "Systems/MoveSystem.h"
#include "Systems/CheckerboardSystem.h"
#include "Systems/CursorSystem.h"
#include "Systems/PlayerSystem.h"

Game::Game()
{
    new CursorSystem();
    new PlayerSystem();
    
    new MoveSystem();
    new CheckboardSystem();
}

Game::~Game()
{

}


void Game::OnUpdate(float)
{   

}

void Game::OnInitilized()
{
    ME_GAME_LOG("Game Initilzed \n");

    auto eManager = Me::EntityManager::GetEntityManager();

    auto e = Me::EntityManager::CreateEntity();

    auto tC = new Me::TransformComponent();
    auto rC = new Me::RenderComponent();
    
    tC->m_position = Me::Math::Vec3(0, 0 , 1.0f);
    tC->m_uniformScale = 32;
            

    rC->m_mesh = Me::Resources::MeshLibrary::GetMeshIndex(Me::Primitives::Quad);
    auto shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/FlatColour_Shader.hlsl");

    if(shader == 0)
    {
        Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/Default_Shader.glsl");
    }

    rC->m_shader = shader;
    rC->m_colour = Me::Colours::RED;

    auto mC = new MoveComponent();

    eManager->AddComponent<MoveComponent>(e, mC);
    eManager->AddComponent<Me::TransformComponent>(e, tC);
    eManager->AddComponent<Me::RenderComponent>(e, rC);

}

void Game::OnClose()
{
    ME_GAME_LOG("Game Closed \n");
}

//Create the game "Application"
Me::Application* Me::CreateApplication()
{
	return new Game();
}