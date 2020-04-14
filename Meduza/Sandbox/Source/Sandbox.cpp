#include "pch.h"
#include "Sandbox.h"

#define WIN 1

#include "../../Meduza/Include/Core/Meduza.h"

Sandbox::Sandbox()
{

	meduza::API::OpenGL;
	m_meduza = new meduza::Meduza(meduza::API::DirectX12);

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
		m_meduza->Clear(meduza::Colours::CELESTIAL_BLUE);

		//Game Update
		Update(0);

		m_meduza->Render();
	}
}
