#pragma once


class Sandbox
{
public:
	Sandbox(bool a_run = false);
	~Sandbox();

	void Run();

	void ImGuiUpdate();

private:
	float m_colour[4];
	bool m_sandboxRun = false;
};

