#include "PCH.h"

#include "Systems/Chess/ChessPawnSystem.h"
#include "Games/Chess/ChessHelper.h"

Chess::ChessPawnSystem::ChessPawnSystem()
{

}

void Chess::ChessPawnSystem::OnUpdate(float)
{
    for(auto& compTuple : m_components)
    {     
        ChessPawnComponent* pawnComp = std::get<ChessPawnComponent*>(compTuple); 
        
    }
}