#include "pch.h"
#include "Sandbox.h"

#include "../../Meduza/Include/Core/Meduza.h"

Sandbox::Sandbox()
{

	m_meduza = new meduza::Meduza(meduza::API::DirectX12);
	printf("Window title = %s \n", m_meduza->GetWindowName().c_str());
}

Sandbox::~Sandbox()
{
	delete m_meduza;
}

void Sandbox::Update(float)
{	
	//Game Update Loop
	m_meduza->Peek();
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
