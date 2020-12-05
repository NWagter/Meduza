#include "PCH.h"
#include "Sandbox.h"
#include "Meduza.h"

#include "MeduzaIncluder.h"
#include "Games/Chess/ChessGame.h"

#include "Systems/CursorSystem.h"
#include "Systems/PlayerSystem.h"

Sandbox::Sandbox()
{
    new CursorSystem();
    new PlayerSystem();

    m_game = new Chess::ChessGame();    
    SetName(m_game->GetGameName() + " | Meduza");
}

Sandbox::~Sandbox()
{

}


void Sandbox::OnUpdate(float)
{   

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