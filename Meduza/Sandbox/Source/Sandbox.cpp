#include "Sandbox.h"

#include "Core/Meduza.h"

Sandbox::Sandbox(bool a_run)
{
	m_sandboxRun = a_run;

	m_colour[0] = 0.4f;
	m_colour[1] = 0.6f;
	m_colour[2] = 0.9f;
	m_colour[3] = 1.0f;
}

Sandbox::~Sandbox()
{
}

void Sandbox::Update(float)
{	

}

void Sandbox::Run()
{

	while (m_sandboxRun)
	{


	}
}

void Sandbox::ImGuiUpdate()
{
	
}
