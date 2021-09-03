#include "PCH.h"

#include "Systems/Chess/ChessPawnSystem.h"

#include "Games/Chess/ChessHelper.h"

Chess::ChessPawnSystem::ChessPawnSystem()
{

}

void Chess::ChessPawnSystem::OnUpdate(float a_dt)
{
    for(auto& compTuple : m_components)
    {     
        ChessPawnComponent* pawnComp = std::get<ChessPawnComponent*>(compTuple); 
        Me::TransformComponent* transComp = std::get<Me::TransformComponent*>(compTuple); 
        
        int x = transComp->m_translation.m_x;
        int y = transComp->m_translation.m_y;

        if(x != pawnComp->m_boardPos.m_x * gs_tileSize || y != pawnComp->m_boardPos.m_y * gs_tileSize)
        {
            if(pawnComp->m_firstMove)
            {
                pawnComp->m_firstMove = false;
            }
            
            Me::Math::Vec3 pos = Me::Math::Vec3(
                pawnComp->m_boardPos.m_x * gs_tileSize,
                pawnComp->m_boardPos.m_y * gs_tileSize,
                transComp->m_translation.m_z);
                
            transComp->m_translation = (Me::Math::MoveTowards(transComp->m_translation, pos, gs_pawnSpeed * a_dt));
        }
    }
}