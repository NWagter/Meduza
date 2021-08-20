#pragma once

#include "Games/BaseGame.h"

namespace Me
{
    class EntityManager;
}

class ExampleScene : public BaseGame
{
    public:
        ExampleScene();
        ~ExampleScene();

        void InitGame() override;
        void UpdateGame(float) override;

    private:
        void CreateFloor(Me::EntityManager&);
};