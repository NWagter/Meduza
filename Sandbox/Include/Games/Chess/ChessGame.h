#pragma once

#include "Games/BaseGame.h"

namespace Chess
{
    class ChessGame : public BaseGame
    {
    public:
        ChessGame();
        ~ChessGame();

        void InitGame() override;
    };
}
