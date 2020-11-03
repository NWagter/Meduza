#pragma once

#include "Core/Application.h"

class Game final : public Me::Application
{
public:
	Game();
	~Game() override;

    void OnUpdate(float) override;
    void OnInitilized() override;
    void OnClose() override;
};