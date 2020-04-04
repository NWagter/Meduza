#include "pch.h"
#include "Sandbox.h"

#include "../../Meduza/Include/Core/Meduza.h"


Sandbox::Sandbox()
{
	m_meduza = new meduza::Meduza();

	m_colour[0] = 0.29f;
	m_colour[1] = 0.59f;
	m_colour[2] = 0.82f;
	m_colour[3] = 1.0f;
}

Sandbox::~Sandbox()
{
	delete m_meduza;
}

void Sandbox::Update(float)
{	
	//Game Update Loop
}

void Sandbox::Run()
{
	while (m_meduza->IsWindowActive())
	{
#ifdef DEV
		OPTICK_FRAME("MainThread");
		OPTICK_CATEGORY(OPTICK_FUNC, Optick::Category::Debug);
#endif // DEV
		m_meduza->Clear(m_colour);

		//Game Update
		Update(0);

		m_meduza->Render();
	}
}
