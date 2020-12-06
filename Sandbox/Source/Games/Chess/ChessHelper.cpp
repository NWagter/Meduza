#include "PCH.h"
#include "MeduzaIncluder.h"

#include "Games/Chess/ChessHelper.h"

#include "Components/Chess/ChessPawnComponent.h"

void Chess::ChessHelper::LogType(ChessPawnComponent& a_pawn)
{
    switch (a_pawn.m_pawnType)
    {
        case Pawns::Pawn :
            ME_GAME_LOG("Pawn \n");
            break;
        case Pawns::Knight :
            ME_GAME_LOG("Knight \n");
        break;
        case Pawns::Rook :
            ME_GAME_LOG("Rook \n");
        break;
        case Pawns::Bishop :
            ME_GAME_LOG("Bishop \n");
        break;
        case Pawns::Queen :
            ME_GAME_LOG("Queen \n");
        break;
        case Pawns::King :
            ME_GAME_LOG("King \n");
        break;
    }
}