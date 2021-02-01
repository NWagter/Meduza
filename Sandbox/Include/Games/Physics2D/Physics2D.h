#pragma once

#include "Games/BaseGame.h"

namespace Physics
{
    class Physics2D : public BaseGame
    {
    public:
        Physics2D();
        ~Physics2D();

        void InitGame() override;
        void UpdateGame(float) override;
    private:
        void SetupScene();
        void SpawnObjects();
    };
}
