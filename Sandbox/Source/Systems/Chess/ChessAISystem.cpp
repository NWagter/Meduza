#include "PCH.h"

#include "Systems/Chess/ChessAISystem.h"

#include "Games/Chess/ChessHelper.h"
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

        //AI logics
    }
}