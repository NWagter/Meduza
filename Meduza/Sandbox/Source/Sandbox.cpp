#include "pch.h"
#include "Sandbox.h"

#define WINDOWS
#define OPTICK

#include <Meduza.h>
#include <Drawable/Sprite.h>
#include <Event/EventSystem.h>
#include <Gfx/Animator2D.h>

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

	s.SetSize(32, 32);
	s.SetUV(32 * 17, 0, 32, 32);


	meduza::gfx::Animator2D animator = meduza::gfx::Animator2D();

	animator.CreateAnimation2D("UP", 0.2f, m_meduza->LoadTexture("Data/Textures/sprites.png"));
	meduza::math::Vec4 rect{ 32 * 17, 0, 32, 32 };
	animator.GetAnimation("UP").AddFrame(rect);
	rect = { (32 * 17) + (32 * 8), 0, 32, 32 };
	animator.GetAnimation("UP").AddFrame(rect);
	rect = { (32 * 17) + (32 * 16), 0, 32, 32 };
	animator.GetAnimation("UP").AddFrame(rect);

	animator.CreateAnimation2D("RIGHT", 0.2f, m_meduza->LoadTexture("Data/Textures/sprites.png"));
	rect = { 32 * 19, 0, 32, 32 };
	animator.GetAnimation("RIGHT").AddFrame(rect);
	rect = { (32 * 19) + (32 * 8), 0, 32, 32 };
	animator.GetAnimation("RIGHT").AddFrame(rect);
	rect = { (32 * 19) + (32 * 16), 0, 32, 32 };
	animator.GetAnimation("RIGHT").AddFrame(rect);

	animator.CreateAnimation2D("DOWN", 0.2f, m_meduza->LoadTexture("Data/Textures/sprites.png"));
	rect = { 32 * 21, 0, 32, 32 };
	animator.GetAnimation("DOWN").AddFrame(rect);
	rect = { (32 * 21) + (32 * 8), 0, 32, 32 };
	animator.GetAnimation("DOWN").AddFrame(rect);
	rect = { (32 * 21) + (32 * 16), 0, 32, 32 };
	animator.GetAnimation("DOWN").AddFrame(rect);

	animator.CreateAnimation2D("LEFT", 0.2f, m_meduza->LoadTexture("Data/Textures/sprites.png"));
	rect = { 32 * 23, 0, 32, 32 };
	animator.GetAnimation("LEFT").AddFrame(rect);
	rect = { (32 * 23) + (32 * 8), 0, 32, 32 };
	animator.GetAnimation("LEFT").AddFrame(rect);
	rect = { (32 * 23) + (32 * 16), 0, 32, 32 };
	animator.GetAnimation("LEFT").AddFrame(rect);

	meduza::math::Vec3 camPos(0, 0, 0);

	animator.SetSprite(s);
	animator.SetAnimation("DOWN");

	while (m_meduza->IsWindowActive())
	{
		m_meduza->Clear(c);
		m_meduza->Peek();

		m_meduza->SetCamEye(camPos);
		animator.Play();
		s.Submit(m_meduza->GetGfx());

		if (meduza::EventSystem::GetEventSystem()->GetEvent(meduza::events::Event::WindowResize))
		{
			m_meduza->SetView(m_meduza->GetWindowSize());
		}
		if (meduza::EventSystem::GetEventSystem()->IsKeyDown(meduza::events::keyCodes::g_keyCode_W))
		{
			animator.SetAnimation("UP");
		}
		if (meduza::EventSystem::GetEventSystem()->IsKeyDown(meduza::events::keyCodes::g_keyCode_S))
		{
			animator.SetAnimation("DOWN");
		}
		if (meduza::EventSystem::GetEventSystem()->IsKeyDown(meduza::events::keyCodes::g_keyCode_D))
		{
			animator.SetAnimation("RIGHT");
		}
		if (meduza::EventSystem::GetEventSystem()->IsKeyDown(meduza::events::keyCodes::g_keyCode_A))
		{
			animator.SetAnimation("LEFT");
		}

		m_meduza->SwapBuffers();

	}
}
