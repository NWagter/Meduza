#include "pch.h"
#include "Sandbox.h"

#define WINDOWS
#define OPTICK

#include <Meduza.h>

#include <Renderable/Renderable2D.h>
#include <Scene/Scene.h>

#include <Gfx/Animator2D.h>
#include <Event/EventSystem.h>
#include <Util/Timer.h>

#ifdef WINDOWS
	meduza::API g_api = meduza::API::DirectX12;
#elif defined(LINUX)
	meduza::API g_api = meduza::API::ES2;
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

	meduza::Shader& colourShaderGLSL = m_meduza->GetShader("Data/Shaders/GLSL/GL_DefaultShader.glsl");
	meduza::Shader& colourShaderHLSL = m_meduza->GetShader("Data/Shaders/HLSL/DX_DefaultShader.hlsl");

	meduza::Material& testMaterial = m_meduza->CreateMaterial(&colourShaderGLSL, "testMaterial");
	meduza::Material& testMaterial2 = m_meduza->CreateMaterial(&colourShaderGLSL, "testMaterial2");
	meduza::Material& testMaterial3 = m_meduza->CreateMaterial(&colourShaderHLSL, "testMaterial3");
	meduza::Material& testMaterial4 = m_meduza->CreateMaterial(&colourShaderHLSL, "testMaterial4");

	float c[] = { 0, 0, 0, 1 };
	m_meduza->SetMaterialParameter(testMaterial, "a_colour", c);
	m_meduza->SetMaterialParameter(testMaterial3, "a_colour", c);
	float c2[] = { 1, 1, 1, 1 };
	m_meduza->SetMaterialParameter(testMaterial2, "a_colour", c2);
	m_meduza->SetMaterialParameter(testMaterial4, "a_colour", c2);

	meduza::Scene sceneGLSL;
	meduza::Scene sceneHLSL;

	//Dirty checkboard generator..
	bool checker = false;
	for (int x = 0; x < 32; x++)
	{
		for (int y = 0; y < 32; y++)
		{
			meduza::Renderable2D* renderable = new meduza::Renderable2D();

			if (checker)
			{
				if (y % 2)
				{
					renderable->SetMaterial(testMaterial);
				}
				else
				{
					renderable->SetMaterial(testMaterial2);
				}
			}
			else
			{
				if (y % 2)
				{
					renderable->SetMaterial(testMaterial2);
				}
				else
				{
					renderable->SetMaterial(testMaterial);
				}
			}

			renderable->SetUnitsPerPixel(16);

			renderable->GetTransform().SetPosition(meduza::math::Vec2(float(x * 16), float(y * 16)));

			sceneGLSL.Submit(*renderable);
		}
		checker = !checker;
	}

	checker = false;
	for (int x = 0; x < 32; x++)
	{
		for (int y = 0; y < 32; y++)
		{
			meduza::Renderable2D* renderable = new meduza::Renderable2D();

			if (checker)
			{
				if (y % 2)
				{
					renderable->SetMaterial(testMaterial3);
				}
				else
				{
					renderable->SetMaterial(testMaterial4);
				}
			}
			else
			{
				if (y % 2)
				{
					renderable->SetMaterial(testMaterial4);
				}
				else
				{
					renderable->SetMaterial(testMaterial3);
				}
			}

			renderable->SetUnitsPerPixel(16);

			renderable->GetTransform().SetPosition(meduza::math::Vec2(float(x * 16), float(y * 16)));

			sceneHLSL.Submit(*renderable);
		}
		checker = !checker;
	}



	meduza::utils::Timer<float> deltaTimer;

	meduza::API currentAPI = m_meduza->GetCurrentAPI();

	while (m_meduza->IsWindowActive())
	{
		const float deltaSeconds = deltaTimer.GetElapsedTime();

		currentAPI = m_meduza->GetCurrentAPI();
		m_meduza->Clear();
		m_meduza->Peek();
		m_meduza->Update(deltaSeconds);

		m_meduza->SetCamEye(playerPos);

		if (currentAPI == meduza::API::OpenGL)
		{
			m_meduza->Submit(sceneGLSL);
		}
		else
		{
			m_meduza->Submit(sceneHLSL);
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

	sceneGLSL.Destroy();
}
