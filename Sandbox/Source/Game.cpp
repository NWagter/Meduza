#include "PCH.h"
#include "Game.h"
#include "Meduza.h"

Game::Game()
{

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

int main()
{
    auto app = new Game();
    if(!app->Run())
    {
        ME_CORE_LOG("Can't Create Game! \n");
    }

    delete app;

    return 0;
}