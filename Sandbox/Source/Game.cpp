#include "PCH.h"
#include "Game.h"
#include "Meduza.h"

#include "MeduzaIncluder.h"

#include "Systems/PawnSystem.h"
#include "Systems/ChessboardSystem.h"
#include "Systems/CursorSystem.h"
#include "Systems/PlayerSystem.h"

Game::Game()
{
    new CursorSystem();
    new PlayerSystem();
    
    new PawnSystem();
    new ChessboardSystem();
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