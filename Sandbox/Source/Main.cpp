#include "PCH.h"
#include "Game.h"

int main()
{
    auto app = new Game();
    if(!app->Run())
    {

    }

    delete app;

    return 0;
}