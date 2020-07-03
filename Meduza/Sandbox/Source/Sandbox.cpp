#include "pch.h"
#include "Sandbox.h"

#define WINDOWS
#define OPTICK

#include <Meduza.h>
#include <Drawable/Sprite.h>
#include <Gfx/Animator2D.h>
#include <Event/EventSystem.h>
#include <Util/Timer.h>

#ifdef WINDOWS
	meduza::API const g_api = meduza::API::OpenGL;
#elif defined(LINUX)
	meduza::API const g_api = meduza::API::ES2;
#endif


Sandbox::Sandbox()
{
	m_meduza = new meduza::Meduza(g_api);

	m_meduza->EnableImGui();
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
	meduza::math::Vec3 playerPos(0, 0, 0);
	float camMoveSpeed = 50;
	
	meduza::Texture& charTexture = m_meduza->GetTexture("Data/Textures/chara_hero.png");
	meduza::Shader& textureShader = m_meduza->GetShader("Data/Shaders/TextureShader.glsl");
	meduza::Material& playerMaterial = m_meduza->CreateMaterial(&textureShader, "PlayerMaterial");

	meduza::drawable::Sprite player;

	player.UseShader(textureShader);
	player.UseTexture(charTexture);

	if (&playerMaterial != nullptr)
	{
		float colour[] = { 1,1,0,1 };
		m_meduza->SetMaterialParameter(playerMaterial, "a_colour", colour);
		player.SetMaterial(playerMaterial);

	}

	player.SetSize(64, 64);
	player.SetUV(0, 0, 48, 48);
	player.SetPosition(0, 0);

	meduza::utils::Timer<float> deltaTimer;

	while (m_meduza->IsWindowActive())
	{
		const float deltaSeconds = deltaTimer.GetElapsedTime();

		m_meduza->Clear();
		m_meduza->Peek();
		m_meduza->Update(deltaSeconds);

		m_meduza->SetCamEye(playerPos);

		if (m_meduza->GetCurrentAPI() == meduza::API::OpenGL)
		{
			player.SetPosition(playerPos.m_x, playerPos.m_y);
			player.Submit(m_meduza->GetGfx());
		}

		if (meduza::EventSystem::GetEventSystem()->GetEvent(meduza::events::Event::WindowResize))
		{
			m_meduza->SetView(m_meduza->GetWindowSize());
		}
		if (meduza::EventSystem::GetEventSystem()->IsKeyDown(meduza::events::keyCodes::g_keyCode_W))
		{
			playerPos.m_y += (camMoveSpeed * deltaSeconds);
		}
		if (meduza::EventSystem::GetEventSystem()->IsKeyDown(meduza::events::keyCodes::g_keyCode_S))
		{
			playerPos.m_y -= (camMoveSpeed * deltaSeconds);
		}
		if (meduza::EventSystem::GetEventSystem()->IsKeyDown(meduza::events::keyCodes::g_keyCode_D))
		{
			playerPos.m_x += (camMoveSpeed * deltaSeconds);
		}
		if (meduza::EventSystem::GetEventSystem()->IsKeyDown(meduza::events::keyCodes::g_keyCode_A))
		{
			playerPos.m_x -= (camMoveSpeed * deltaSeconds);
		}


		m_meduza->SwapBuffers();
	}
}
