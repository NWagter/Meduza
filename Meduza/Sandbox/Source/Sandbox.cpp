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
	std::vector<meduza::drawable::Drawable*> sprites;

	sprites.emplace_back(new meduza::drawable::Sprite());
	sprites.emplace_back(new meduza::drawable::Sprite());

	dynamic_cast<meduza::drawable::Sprite*>(sprites[0])->SetPosition(0.5f, 0);

	dynamic_cast<meduza::drawable::Sprite*>(sprites[1])->SetPosition(-0.5f, 0);

	sprites[0]->SetColour(meduza::math::Vec4(1, 1, 1, 1));

	std::string texture = m_meduza->LoadTexture("Data/Textures/sprites.png");
	sprites[0]->UseTexture(texture);

	//Add Shader to Sprite
	std::string name = m_meduza->LoadShader("Data/Shaders/TextureShader.glsl");
	sprites[0]->UseShader(name);

	//Set Sprite UV
	dynamic_cast<meduza::drawable::Sprite*>(sprites[0])->SetUV(32, 0, 32, 32);

	sprites[1]->SetColour(meduza::math::Vec4(1,0,1,1));

	meduza::math::Vec2 wSize = m_meduza->GetWindowSize();

	meduza::math::Vec2 nWSize = wSize * 0.01f;
	meduza::math::Vec4 frustrum = { -nWSize.m_x,nWSize.m_x, -nWSize.m_y, nWSize.m_y };

	m_meduza->SetNewCamera(meduza::CameraPerspective::Orthographic, frustrum);

	meduza::math::Vec2 pos = { sprites[0]->GetPos().m_x, sprites[0]->GetPos().m_y };
	bool moveLeft = true;

	while (m_meduza->IsWindowActive())
	{
#if defined(WINDOWS) && defined(OPTICK)
		OPTICK_FRAME("MainThread");
		OPTICK_CATEGORY(OPTICK_FUNC, Optick::Category::Debug);
#endif // 
		m_meduza->Clear(meduza::Colours::CELESTIAL_BLUE);
		m_meduza->Submit(sprites);

		if (moveLeft)
		{
			if (pos.m_x < -5)
				moveLeft = false;

			dynamic_cast<meduza::drawable::Sprite*>(sprites[0])->SetUV(32 * 38, 0, 32, 32);
			pos.m_x -= 0.05f;
		}
		else if (!moveLeft)
		{
			if (pos.m_x > 5)
				moveLeft = true;

			dynamic_cast<meduza::drawable::Sprite*>(sprites[0])->SetUV(32 * 35, 0, 32, 32);
			pos.m_x += 0.05f;
		}

		meduza::events::Event e;
		while (m_meduza->ReadEvent(e))
		{


			if (e.m_event == meduza::events::Events::WindowEvent)
			{
				switch (e.m_type)
				{
				case meduza::events::EventType::WindowResize:
					wSize = meduza::math::Vec2(float(e.GetValueA()), float(e.GetValueB()));
					nWSize = wSize * 0.01f;
					frustrum = { -nWSize.m_x,nWSize.m_x, -nWSize.m_y, nWSize.m_y };

					m_meduza->SetView(frustrum);
					break;
				}
			}
		}

		m_meduza->SetCamEye(meduza::math::Vec3(pos.m_x, pos.m_y, 0));
		dynamic_cast<meduza::drawable::Sprite*>(sprites[0])->SetPosition(pos);
		
		//Game Update
		Update(0);

		m_meduza->SwapBuffers();
	}

	for (auto d : sprites)
	{
		delete d;
	}
}
