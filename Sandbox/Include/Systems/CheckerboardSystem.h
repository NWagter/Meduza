#pragma once

#include "ECS/BaseSystem.h"

#include "Components/TileComponent.h"

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
    EntityID m_playerEntity;

};