#pragma once

#include "Games/BaseGame.h"

namespace Me
{
    class EntityManager;
    using Mesh = uint16_t;
}

class EmptyGame : public BaseGame
{
public:
    EmptyGame();
    ~EmptyGame();

    void InitGame() override;

private:
    void CreateObject(float,float,float, Me::EntityManager*, bool = false, bool = true);
    void CreateObject(float,float,float, Me::EntityManager*, Me::Mesh, bool = true);
};
