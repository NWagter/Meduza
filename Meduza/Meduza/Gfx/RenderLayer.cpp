#include "pch\pch.h"
#include "RenderLayer.h"

#include "Window/Window.h"

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
