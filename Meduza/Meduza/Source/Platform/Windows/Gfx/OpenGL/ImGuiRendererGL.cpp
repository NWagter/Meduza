#include "mePch.h"

#include "Platform/Windows/Gfx/OpenGL/ImGuiRendererGL.h"

meduza::ImGuiRendererGL::ImGuiRendererGL(renderer::Renderer&)
{
	ImGui_ImplOpenGL3_Init("#version 410");
}

meduza::ImGuiRendererGL::~ImGuiRendererGL()
{
	ImGui_ImplOpenGL3_Shutdown();
}

void meduza::ImGuiRendererGL::Clear()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void meduza::ImGuiRendererGL::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
