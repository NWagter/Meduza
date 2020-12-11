#pragma once

#include "Games/BaseGame.h"

class EmptyGame : public BaseGame
{
public:
    EmptyGame();
    ~EmptyGame();

    void InitGame() override;

private:
};
