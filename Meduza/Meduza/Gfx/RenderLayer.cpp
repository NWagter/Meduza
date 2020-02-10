#include "pch\pch.h"
#include "RenderLayer.h"

#include "Window/Window.h"

RenderLayer::~RenderLayer()
{
	for (int i = 0; i < m_renderItems.size(); i++)
	{
		delete m_renderItems[i];
	}
}

bool RenderLayer::IsWindowActive()
{
	return m_window->IsWindowActive();;
}

void RenderLayer::InitImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	m_io = ImGui::GetIO(); (void)m_io;
	m_io.Fonts->AddFontDefault();
	ImGui::StyleColorsDark();

}
