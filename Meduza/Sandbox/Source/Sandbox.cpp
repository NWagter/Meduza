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
	meduza::Colour c = meduza::Colours::CELESTIAL_BLUE;

	int w = 320 / 16;
	int h = 384 / 16;

	std::vector<meduza::drawable::Drawable*> tiles;
	int counter = 24000;
	int i = 0;
	while(counter > 0)
	{
		float offset = float(i * w) * 32;
		i++;
		
		for (int x = (w - 1); x >= 0; x--)
		{
			if (counter < 0)
				break;
			for (int y = h; y > 0; y--)
			{
				counter--;

				if (counter < 0)
					break;
				meduza::drawable::Sprite* sprite = new meduza::drawable::Sprite();
				sprite->UseShader(m_meduza->LoadShader("Data/Shaders/TextureShader.glsl"));
				sprite->UseTexture(m_meduza->LoadTexture("Data/Textures/tiles_dungeon_v1.1.png"));
				sprite->SetSize(32, 32);
				sprite->SetUV(float(16 * x), float(16 * (h - y)), 16, 16);
				sprite->SetPosition(float(x * 32) + offset, float(y * 32));
				tiles.push_back(sprite);
			}
		}
	}

	meduza::drawable::Sprite player;
	player.UseShader(m_meduza->LoadShader("Data/Shaders/TextureShader.glsl"));
	player.UseTexture(m_meduza->LoadTexture("Data/Textures/chara_hero.png"));
	player.SetSize(64, 64);
	player.SetUV(0, 0, 48, 48);
	player.SetPosition(0, 0);

	meduza::gfx::Animator2D animator = meduza::gfx::Animator2D();

	animator.CreateAnimation2D("UP", 0.2f, m_meduza->LoadTexture("Data/Textures/chara_hero.png"));
	meduza::math::Vec4 rect{ 48 * 0, 48 * 4, 48, 48 };
	animator.GetAnimation("UP").AddFrame(rect);
	rect = { 48 * 1, 48 * 4, 48, 48 };
	animator.GetAnimation("UP").AddFrame(rect);
	rect = { 48 * 2, 48 * 4, 48, 48 };
	animator.GetAnimation("UP").AddFrame(rect);
	rect = { 48 * 3, 48 * 4, 48, 48 };
	animator.GetAnimation("UP").AddFrame(rect);

	animator.CreateAnimation2D("RIGHT", 0.2f, m_meduza->LoadTexture("Data/Textures/chara_hero.png"));
	rect = { 48 * 0, 48 * 3, 48, 48 };
	animator.GetAnimation("RIGHT").AddFrame(rect);
	rect = { 48 * 1, 48 * 3, 48, 48 };
	animator.GetAnimation("RIGHT").AddFrame(rect);
	rect = { 48 * 2, 48 * 3, 48, 48 };
	animator.GetAnimation("RIGHT").AddFrame(rect);
	rect = { 48 * 3, 48 * 3, 48, 48 };
	animator.GetAnimation("RIGHT").AddFrame(rect);

	animator.CreateAnimation2D("DOWN", 0.2f, m_meduza->LoadTexture("Data/Textures/chara_hero.png"));
	rect = { 48 * 0, 48 * 2, 48, 48 };
	animator.GetAnimation("DOWN").AddFrame(rect);
	rect = { 48 * 1, 48 * 2, 48, 48 };
	animator.GetAnimation("DOWN").AddFrame(rect);
	rect = { 48 * 2, 48 * 2, 48, 48 };
	animator.GetAnimation("DOWN").AddFrame(rect);
	rect = { 48 * 3, 48 * 2, 48, 48 };
	animator.GetAnimation("DOWN").AddFrame(rect);

	animator.CreateAnimation2D("LEFT", 0.2f, m_meduza->LoadTexture("Data/Textures/chara_hero.png"));
	rect = { 48 * 1, 48 * 3, -48, 48 };
	animator.GetAnimation("LEFT").AddFrame(rect);
	rect = { 48 * 2, 48 * 3, -48, 48 };
	animator.GetAnimation("LEFT").AddFrame(rect);
	rect = { 48 * 3, 48 * 3, -48, 48 };
	animator.GetAnimation("LEFT").AddFrame(rect);
	rect = { 48 * 4, 48 * 3, -48,48 };
	animator.GetAnimation("LEFT").AddFrame(rect);

	meduza::math::Vec3 playerPos(0, 0, 0);

	animator.SetSprite(player);
	animator.SetAnimation("DOWN");

	float camMoveSpeed = 50;

	meduza::utils::Timer<float> deltaTimer;
	float totalTime = 0.f;
	float fps = 0;
	unsigned frameCount = 0;


	while (m_meduza->IsWindowActive())
	{
		const float deltaSeconds = deltaTimer.GetElapsedTime();
		m_meduza->Clear(c);
		m_meduza->Peek();


		animator.Play();

		m_meduza->SetCamEye(playerPos);
		m_meduza->Submit(tiles);

		player.SetPosition(playerPos.m_x, playerPos.m_y);
		player.Submit(m_meduza->GetGfx());


		if (meduza::EventSystem::GetEventSystem()->GetEvent(meduza::events::Event::WindowResize))
		{
			m_meduza->SetView(m_meduza->GetWindowSize());
		}
		if (meduza::EventSystem::GetEventSystem()->IsKeyDown(meduza::events::keyCodes::g_keyCode_W))
		{
			animator.SetAnimation("UP");
			playerPos.m_y += (camMoveSpeed * deltaSeconds);
		}
		if (meduza::EventSystem::GetEventSystem()->IsKeyDown(meduza::events::keyCodes::g_keyCode_S))
		{
			animator.SetAnimation("DOWN");
			playerPos.m_y -= (camMoveSpeed * deltaSeconds);
		}
		if (meduza::EventSystem::GetEventSystem()->IsKeyDown(meduza::events::keyCodes::g_keyCode_D))
		{
			animator.SetAnimation("RIGHT");
			playerPos.m_x += (camMoveSpeed * deltaSeconds);
		}
		if (meduza::EventSystem::GetEventSystem()->IsKeyDown(meduza::events::keyCodes::g_keyCode_A))
		{
			animator.SetAnimation("LEFT");
			playerPos.m_x -= (camMoveSpeed * deltaSeconds);
		}

		m_meduza->DebugDrawStats(fps);
		m_meduza->SwapBuffers();

		//Calculate the fps
		totalTime += deltaSeconds;
		frameCount++;
		if (totalTime >= 1.f)
		{
			fps = float(frameCount) / totalTime;
			frameCount = 0;
			totalTime = 0.f;
			printf("[FPS COUNTER] : fps %f \n", fps);
		}
	}

	for (auto t : tiles)
	{
		delete t;
	}
}
