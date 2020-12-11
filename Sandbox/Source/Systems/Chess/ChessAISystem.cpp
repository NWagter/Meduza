#include "PCH.h"

#include "Systems/Chess/ChessAISystem.h"

#include "Games/Chess/ChessHelper.h"

#include "Components/Chess/ChessPawnComponent.h"
#include "Components/Chess/ChessBoardComponent.h"

Chess::ChessAISystem::ChessAISystem()
{

}

void Chess::ChessAISystem::OnUpdate(float)
{
    for(auto& compTuple : m_components)
    {             
        ChessAIComponent* aiComp = std::get<ChessAIComponent*>(compTuple); 
        if(aiComp->m_board->m_activePlayer != aiComp->m_aiColour)
        {
            continue;
        }
        auto board = aiComp->m_board;

// Fetch my pieces
        std::vector<ChessPawnComponent*> pawns;

        for(int x = gs_boardWidth - 1; x > 0; --x)
        {
            for(int y = gs_boardWidth -1 ; y > 0; --y)
            {
                ChessPawnComponent* piece = board->m_board[x][y];

                if(piece != nullptr && piece->m_pawnColour == aiComp->m_aiColour)
                {
                    pawns.push_back(piece);
                }
            }
        }

        std::pair<int,int> bestMove = std::pair<int,int>(0,0);
        ChessPawnComponent* pawn = nullptr;
        int v = 0;
        for(auto p : pawns)
        {
            auto moves = ChessHelper::GetPossibleMoves(*p, board);

            auto pawnBestMove = ChessHelper::GetBestMove(moves, board);
            int vCheck = pawnBestMove.second;
            if(vCheck < v)
            {
                v = vCheck;
                bestMove = moves[pawnBestMove.first];
                pawn = p;
            }
        }

        if(pawn != nullptr)
        {
            Me::Math::Vec2 pos = pawn->m_boardPos;
            board->m_board[static_cast<int>(pos.m_x)][static_cast<int>(pos.m_y)] = nullptr;
            pawn->m_boardPos = Me::Math::Vec2(bestMove.first,bestMove.second);
            if(board->m_board[bestMove.first][bestMove.second] != nullptr)
            {
                Me::EntityManager::DestroyEntity(board->m_board[bestMove.first][bestMove.second]->m_pawnEntity);
            }
            board->m_board[bestMove.first][bestMove.second] = pawn;

            board->m_activePlayer = Colour::White;
        }
        //AI logics
    }
}