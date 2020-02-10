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
	float m_shaderTest = 0;
	bool m_sandboxRun = false;
};

