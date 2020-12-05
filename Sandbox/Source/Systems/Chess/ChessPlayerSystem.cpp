#include "PCH.h"

#include "Systems/Chess/ChessPlayerSystem.h"

#include "Games/Chess/ChessHelper.h"
#include "Components/Chess/ChessBoardComponent.h"


Chess::ChessPlayerSystem::ChessPlayerSystem()
{

}

void Chess::ChessPlayerSystem::OnUpdate(float)
{
    for(auto& compTuple : m_components)
    {     
        ChessPlayerComponent* pComp = std::get<ChessPlayerComponent*>(compTuple);
        if(pComp->m_board->m_activePlayer != pComp->m_playerColour)
        {
            continue;
        }
        
        //Player Logics
    }
}