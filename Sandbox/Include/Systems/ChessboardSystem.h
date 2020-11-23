#pragma once

#include "ECS/BaseSystem.h"

#include "Components/ChessBoardComponent.h"
#include "Components/PawnComponent.h"

namespace Me
{    
    struct TransformComponent;
}

class ChessboardSystem : public Me::BaseSystem<ChessBoardComponent>
{
    public:
    ChessboardSystem();

    protected:
        void OnCreate() override;
        void OnUpdate(float) override;

    private:
        void CreateBoard();
        PawnComponent* CreatePieces(int, int);
        
        std::string GetPieceName(PawnTypes);
        TileComponent* GetTile(Me::Math::Vec2, ChessBoardComponent*);
        TileComponent* GetTile(int, int, ChessBoardComponent*);

        bool CheckMove(PawnComponent*, TileComponent*, ChessBoardComponent*);
        bool CheckTiles(Me::Math::Vec2, Me::Math::Vec2, ChessBoardComponent*);

        EntityID m_playerEntity;
        EntityID m_chessEntity;
};