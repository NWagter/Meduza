#pragma once

#include "Core/Application.h"

class BaseGame;

class Sandbox final : public Me::Application
{
public:
	Sandbox();
	~Sandbox() override;

    void OnUpdate(float) override;
    void OnInitilized() override;
    void OnClose() override;

private:
    BaseGame* m_game;
};