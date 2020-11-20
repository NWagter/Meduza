#pragma once

#include "Games/BaseGame.h"

class Chess : public BaseGame
{
public:
    Chess();
    ~Chess();

    void InitGame() override;
};