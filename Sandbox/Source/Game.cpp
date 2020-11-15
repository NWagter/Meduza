#include "PCH.h"
#include "Game.h"
#include "Meduza.h"

#include "MeduzaIncluder.h"

#include "Components/MoveComponent.h"
#include "Systems/MoveSystem.h"

#include "Components/TileComponent.h"
#include "Systems/CheckerboardSystem.h"

Game::Game()
{
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
    
    tC->m_position = Me::Math::Vec3(0,0,0);
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

    eManager->AddComponent(e, tC);
    eManager->AddComponent(e, rC);
    eManager->AddComponent(e, mC);

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