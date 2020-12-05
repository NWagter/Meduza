#pragma once

#include "Games/BaseGame.h"

namespace Chess
{
    struct ChessBoardComponent;

    class ChessGame : public BaseGame
    {
    public:
        ChessGame();
        ~ChessGame();

        void InitGame() override;

    private:
        void CreateBoard();
        void CreatePieces(ChessBoardComponent*);
    };
}
