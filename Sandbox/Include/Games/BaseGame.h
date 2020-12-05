#pragma once

class BaseGame
{
public:
    BaseGame();
    virtual ~BaseGame() = default;

    virtual void InitGame();

    std::string GetGameName() { return m_gameName;}

protected:
    std::string m_gameName = "Base";
};