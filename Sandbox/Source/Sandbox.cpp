#include "PCH.h"
#include "Sandbox.h"
#include "Meduza.h"

#include "Games/BaseGame.h"

#include "MeduzaIncluder.h"


Sandbox::Sandbox() : Me::Application(1280,720, Me::GFX_API::OpenGL)
{
    m_game = new BaseGame();    

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
    delete m_game;
}

//Create the game "Application"
Me::Application *Me::CreateApplication()
{
    return new Sandbox();
}