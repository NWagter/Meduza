#include "pch.h"
#include "Sandbox.h"

#define WIN

#include <Meduza.h>
#include <Drawable/Sprite.h>

Sandbox::Sandbox()
{

	m_meduza = new meduza::Meduza(meduza::API::OpenGL);
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
	std::vector<meduza::drawable::Drawable*> sprites;


	sprites.emplace_back(new meduza::drawable::Sprite());
	sprites.emplace_back(new meduza::drawable::Sprite());
	sprites.emplace_back(new meduza::drawable::Sprite());
	sprites.emplace_back(new meduza::drawable::Sprite());
	sprites.emplace_back(new meduza::drawable::Sprite());
	sprites.emplace_back(new meduza::drawable::Sprite());

	dynamic_cast<meduza::drawable::Sprite*>(sprites[0])->SetPosition(0, 0);

	meduza::math::Vec2 pos(1, 1);
	dynamic_cast<meduza::drawable::Sprite*>(sprites[1])->SetPostion(pos);
	pos = meduza::math::Vec2(4, 6);
	dynamic_cast<meduza::drawable::Sprite*>(sprites[2])->SetPostion(pos);
	pos = meduza::math::Vec2(8, 2);
	dynamic_cast<meduza::drawable::Sprite*>(sprites[4])->SetPostion(pos);
	pos = meduza::math::Vec2(1, 9);
	dynamic_cast<meduza::drawable::Sprite*>(sprites[4])->SetPostion(pos);
	pos = meduza::math::Vec2(14, 5);
	dynamic_cast<meduza::drawable::Sprite*>(sprites[5])->SetPostion(pos);


	while (m_meduza->IsWindowActive())
	{
#ifdef DEV
		OPTICK_FRAME("MainThread");
		OPTICK_CATEGORY(OPTICK_FUNC, Optick::Category::Debug);
#endif // DEV
		m_meduza->Clear(meduza::Colours::CELESTIAL_BLUE);
		m_meduza->Submit(sprites);
		//Game Update
		Update(0);

		m_meduza->Render();
	}
}
