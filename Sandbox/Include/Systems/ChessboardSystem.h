#pragma once

#include "ECS/BaseSystem.h"

#include "Components/TileComponent.h"
#include "Components/PawnComponent.h"

namespace Me
{    
    struct TransformComponent;
}

class ChessboardSystem : public Me::BaseSystem<TileComponent, Me::TransformComponent>
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
        bool CheckMove(PawnComponent*, TileComponent*);

        EntityID m_playerEntity;
};