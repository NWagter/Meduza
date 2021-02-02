#pragma once

class BaseGame
{
public:
    BaseGame();
    virtual ~BaseGame() = default;

    virtual void InitGame();
    virtual void UpdateGame(float);

    std::string GetGameName() { return m_gameName;}

protected:
    std::string m_gameName = "Base";
};