#include "pch.h"
#include "Sandbox.h"

#define WINDOWS
#define OPTICK

#include <Meduza.h>
#include <Drawable/Sprite.h>
#include <Event/EventSystem.h>

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

	meduza::math::Vec3 camPos(0, 0, 0);
	float camSpeed = 15.f;

	while (m_meduza->IsWindowActive())
	{
		OPTICK_FRAME("MainThread");

		m_meduza->Clear(c);

		m_meduza->Peek();

		m_meduza->SetCamEye(camPos);

		s.Submit(m_meduza->GetGfx());

		if (meduza::EventSystem::GetEventSystem()->GetEvent(meduza::events::Event::WindowResize))
		{
			m_meduza->SetView(m_meduza->GetWindowSize());
		}
		if (meduza::EventSystem::GetEventSystem()->IsKeyDown(meduza::events::keyCodes::g_keyCode_W))
		{
			camPos.m_y += camSpeed;
		}
		if (meduza::EventSystem::GetEventSystem()->IsKeyDown(meduza::events::keyCodes::g_keyCode_S))
		{
			camPos.m_y -= camSpeed;
		}
		if (meduza::EventSystem::GetEventSystem()->IsKeyDown(meduza::events::keyCodes::g_keyCode_D))
		{
			camPos.m_x += camSpeed;
		}
		if (meduza::EventSystem::GetEventSystem()->IsKeyDown(meduza::events::keyCodes::g_keyCode_A))
		{
			camPos.m_x -= camSpeed;
		}

		m_meduza->SwapBuffers();

	}
}
