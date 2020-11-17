#pragma once

#include "ECS/BaseSystem.h"

#include "Components/TileComponent.h"
#include "Components/PawnComponent.h"

namespace Me
{    
    struct TransformComponent;
}

class CheckboardSystem : public Me::BaseSystem<TileComponent, Me::TransformComponent>
{
    public:
    CheckboardSystem();

    protected:
        void OnCreate() override;
        void OnUpdate(float) override;

    private:
        void CreateBoard();
        PawnComponent* CreatePieces(int, int);
        std::string GetPieceName(PawnTypes);
    EntityID m_playerEntity;

};