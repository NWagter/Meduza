#pragma once


//================================================================
// Chess Values
//================================================================

static constexpr unsigned int gs_pawnValue = 10;
static constexpr unsigned int gs_knighValue = 30;
static constexpr unsigned int gs_bishnopValue = 30;
static constexpr unsigned int gs_rookValue = 50;
static constexpr unsigned int gs_queenValue = 90;
static constexpr unsigned int gs_kingValue = 900;

namespace Chess
{
    const static unsigned int gs_boardWidth = 8;
    const static unsigned int gs_boardHeight = 8;

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
    struct ChessBoardComponent;
    
    class ChessHelper
    {
        public:
            static void LogType(ChessPawnComponent&);    
            static std::vector<std::pair<int,int>> GetPossibleMoves(ChessPawnComponent&, ChessBoardComponent*);
            static bool CanMove(std::pair<int,int>, std::vector<std::pair<int,int>>);
            static int GetValue(ChessPawnComponent&);
    };
}