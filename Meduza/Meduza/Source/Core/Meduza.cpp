#include "mePch.h"
#include "Core/Meduza.h"

#include "Gfx/Window.h"
#include "Gfx/RenderLayer.h"

me::Meduza::Meduza()
{
	m_window = mr::Window::NewWindow(720, 480, mr::RenderLayer::GetAPI());
	m_renderLayer = mr::RenderLayer::CreateRenderLayer(*m_window);
}

me::Meduza::~Meduza()
{
	delete m_window;
	delete m_renderLayer;
}

void me::Meduza::Update(float)
{
	//Engine Update Loop
	m_window->Peek();
	m_renderLayer->Update();
}

void me::Meduza::Clear(float a_c[4])
{
	m_renderLayer->Clear(a_c);
}

void me::Meduza::Render()
{
	m_renderLayer->Render();
}

bool me::Meduza::IsActive()
{
	return m_window->IsActive();
}



