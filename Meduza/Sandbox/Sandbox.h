#pragma once


#include "../Meduza/Helper/Helper.h"

class Sandbox
{
public:
	Sandbox(bool a_run = false);
	~Sandbox();

	void Update(float);
	void Run();

	void ImGuiUpdate();

private:
	float m_colour[4];
	bool m_sandboxRun = false;
	Drawable d;
	Drawable d2;
	Drawable d3;
	Drawable d4;
	Drawable d5;
};

