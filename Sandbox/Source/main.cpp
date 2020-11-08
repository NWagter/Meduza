#include "PCH.h"
#include "Game.h"

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
