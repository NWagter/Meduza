#include "PCH.h"

#include "MeduzaIncluder.h"

#include "Systems/Chess/ChessPlayerSystem.h"

#include "Games/Chess/ChessHelper.h"
#include "Components/Chess/ChessBoardComponent.h"
#include "Components/Chess/ChessPawnComponent.h"

#include "Components/CursorComponent.h"


Chess::ChessPlayerSystem::ChessPlayerSystem()
{

}

void Chess::ChessPlayerSystem::OnCreate()
{
    auto entList = Me::EntityManager::GetEntityManager()->GetEntities();
    for(auto entt : entList)
    {
        if(entt.second.find(CursorComponent::s_componentID) != entt.second.end())
        {            
            m_cursor = entt.first;
        }
    }
}

void Chess::ChessPlayerSystem::OnUpdate(float)
{
    // Get Mouse Position
    auto mouseComp = Me::EntityManager::GetEntityManager()->GetComponent<CursorComponent>(m_cursor);

    Me::Math::Vec3 mousePos = mouseComp->m_position;
    bool lClick = Me::Event::EventSystem::GetEventSystem()->MouseButtonDown(Me::Event::MouseButton::LButton);
    bool rClick = Me::Event::EventSystem::GetEventSystem()->MouseButtonDown(Me::Event::MouseButton::RButton);

    for(auto& compTuple : m_components)
    {     
        ChessPlayerComponent* pComp = std::get<ChessPlayerComponent*>(compTuple);
        if(pComp->m_board->m_activePlayer != pComp->m_playerColour)
        {
            continue;
        }

        //Player Logics
        if(rClick && pComp->m_selectedPawn != nullptr)
        {
            pComp->m_selectedPawn = nullptr;
            pComp->m_possibleMoves.clear();
        }

        if(lClick)
        {
            int x = (mousePos.m_x + (gs_tileSize / 2)) / gs_tileSize;
            int y = (mousePos.m_y + (gs_tileSize / 2)) / gs_tileSize;

            if(x < gs_boardWidth && x >= 0)
            {
                if(y < gs_boardHeight && y >= 0)
                {
                    auto pawn = pComp->m_board->m_board[x][y];

                    if(pawn != nullptr && pawn->m_pawnColour == pComp->m_playerColour)
                    {
                        pComp->m_possibleMoves = ChessHelper::GetPossibleMoves(*pawn, pComp->m_board);
                        pComp->m_selectedPawn = pawn;
                    }
                    else if(ChessHelper::CanMove(std::pair<int,int>(x,y), pComp->m_possibleMoves))
                    {
                        Me::Math::Vec2 pos = pComp->m_selectedPawn->m_boardPos;
                        pComp->m_board->m_board[static_cast<int>(pos.m_x)][static_cast<int>(pos.m_y)] = nullptr;
                        pComp->m_selectedPawn->m_boardPos = Me::Math::Vec2(x,y);
                        if(pComp->m_board->m_board[x][y] != nullptr)
                        {
                            Me::EntityManager::DestroyEntity(pComp->m_board->m_board[x][y]->m_pawnEntity);
                        }
                        pComp->m_board->m_board[x][y] = pComp->m_selectedPawn;
                        pComp->m_selectedPawn = nullptr;
                        pComp->m_possibleMoves.clear();

                        pComp->m_board->m_activePlayer = Colour::Black;
                    }
                }
            }
        }
    }
}