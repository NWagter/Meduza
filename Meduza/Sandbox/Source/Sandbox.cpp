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

	while (m_meduza->IsWindowActive())
	{
#if defined(WINDOWS) && defined(OPTICK)
		OPTICK_FRAME("MainThread");
		OPTICK_CATEGORY(OPTICK_FUNC, Optick::Category::Debug);
#endif // 
		m_meduza->Clear(meduza::Colours::CELESTIAL_BLUE);
		m_meduza->Submit(sprites);
		//Game Update
		Update(0);

		m_meduza->SwapBuffers();
	}

	for (auto d : sprites)
	{
		delete d;
	}
}
