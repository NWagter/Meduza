#pragma once

#include "Games/BaseGame.h"

namespace Me
{
    class EntityManager;
}

class EmptyGame : public BaseGame
{
public:
    EmptyGame();
    ~EmptyGame();

    void InitGame() override;

private:
    void CreateCube(float,float,float, Me::EntityManager*);
};
