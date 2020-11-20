#include "PCH.h"

#include "Systems/ChessSystem.h"

#include "MeduzaIncluder.h"

ChessSystem::ChessSystem()
{

}

void ChessSystem::OnCreate()
{
    auto entManager = Me::EntityManager::GetEntityManager();
    EntityID entt = entManager->CreateEntity();

    auto comp = new ChessComponent();
    comp->m_movingPawn = nullptr;

    entManager->AddComponent<ChessComponent>(entt, comp);
}

void ChessSystem::OnUpdate(float)
{
    for(auto compTuple : m_components)
    {        
        ChessComponent* chess = std::get<ChessComponent*>(compTuple);

        if(chess->m_movingPawn != nullptr)
        {
           if(!chess->m_movingPawn->m_moving)
           {
               if(chess->m_movingPawn->m_colour == PawnColour::White)
               {
                   chess->m_turn = PawnColour::Black;
               }else
               {
                   chess->m_turn = PawnColour::White;
               }
               


               chess->m_movingPawn = nullptr;

           }
        }
    }
}