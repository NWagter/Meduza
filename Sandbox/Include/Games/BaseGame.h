#pragma once

class BaseGame
{
public:
    virtual ~BaseGame() = default;

    virtual void InitGame() = 0;
};