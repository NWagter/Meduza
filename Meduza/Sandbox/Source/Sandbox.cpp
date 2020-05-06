#include "pch.h"
#include "Sandbox.h"

#define WINDOWS
#define OPTICK

#include <Meduza.h>
#include <Drawable/Sprite.h>

#ifdef WINDOWS
	meduza::API const g_api = meduza::API::OpenGL;
#elif defined(LINUX)
	meduza::API const g_api = meduza::API::ES2;
#endif


Sandbox::Sandbox()
{
	m_meduza = new meduza::Meduza(g_api);

	//m_meduza->EnableImGui();
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
	meduza::Colour c = meduza::Colours::CELESTIAL_BLUE;
	meduza::drawable::Sprite s;

	meduza::math::Vec2 wSize = m_meduza->GetWindowSize();
	m_meduza->SetView(wSize);

	while (m_meduza->IsWindowActive())
	{
		m_meduza->Clear(c);

		s.Submit(m_meduza->GetGfx());
		m_meduza->Peek();

		m_meduza->SwapBuffers();

	}
}
