#pragma once

namespace Chess
{
    const static int gs_boardWidth = 8;
    const static int gs_boardHeight = 8;

    const static int gs_tileSize = 32;

    enum class Pawns
    {
        Pawn = 0,
        Rook,
        Knight,
        Bishop,
        Queen,
        King
    };

    enum class Colour
    {
        White,
        Black
    };

    struct ChessPawnComponent;
    
    class ChessHelper
    {
        public:
            static void LogType(ChessPawnComponent&);    
    };
}