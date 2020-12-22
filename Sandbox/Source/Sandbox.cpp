#include "PCH.h"
#include "Sandbox.h"
#include "Meduza.h"

#include "MeduzaIncluder.h"

#define Run_EmptyTest 0
#define Run_Chess 1

#if Run_EmptyTest
#include "Games/Empty/EmptyGame.h"
#elif Run_Chess
#include "Games/Chess/ChessGame.h"
#endif

#include "Systems/CursorSystem.h"
#include "Systems/PlayerSystem.h"

Sandbox::Sandbox()
{
    new CursorSystem();
    new PlayerSystem();

#if Run_EmptyTest 
    m_game = new EmptyGame();
#elif Run_Chess
    m_game = new Chess::ChessGame();
#endif

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