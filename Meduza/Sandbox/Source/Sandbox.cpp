#include "pch.h"
#include "Sandbox.h"

#include "../../Meduza/Include/Core/Meduza.h"

Sandbox::Sandbox()
{
	m_meduza = new me::Meduza();

	m_colour[0] = 0.4f;
	m_colour[1] = 0.6f;
	m_colour[2] = 0.9f;
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
	while (m_meduza->IsActive())
	{
		m_meduza->Clear(m_colour);
		Update(0);
		m_meduza->Update(0);
		m_meduza->Render();
	}
}
