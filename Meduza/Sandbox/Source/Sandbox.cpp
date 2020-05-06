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

	s.UseShader(m_meduza->LoadShader("Data/Shaders/TextureShader.glsl"));
	s.UseTexture(m_meduza->LoadTexture("Data/Textures/sprites.png"));

	s.SetSize(100, 100);
	s.SetUV(32 * 2, 0, 32, 32);

	while (m_meduza->IsWindowActive())
	{
		m_meduza->Clear(c);

		s.Submit(m_meduza->GetGfx());
		m_meduza->Peek();

		meduza::events::Event e;
		while (m_meduza->ReadEvent(e))
		{
			if (e.m_type == meduza::events::EventType::WindowResize)
			{
				meduza::math::Vec2 size(float(e.GetValueA()), float(e.GetValueB()));
				m_meduza->SetView(size);
			}
		}

		m_meduza->SwapBuffers();

	}
}
