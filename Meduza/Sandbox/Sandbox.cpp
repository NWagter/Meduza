#include "Sandbox.h"

#include "../Meduza/Helper/Helper.h"
#include "../Meduza/Renderer/Meduza.h"

#include "ImGui.h"

Sandbox::Sandbox(bool a_run)
{
	m_sandboxRun = a_run;

	m_colour[0] = 0.4f;
	m_colour[1] = 0.6f;
	m_colour[2] = 0.9f;
	m_colour[3] = 1.0f;
}

Sandbox::~Sandbox()
{
}

void Sandbox::Run()
{
	new Meduza(GfxAPI::DirectX12);

	while (m_sandboxRun) {

		Colour cColour = { m_colour[0], m_colour[1], m_colour[2], m_colour[3] };

		Meduza::Clear(cColour);

		Meduza::Update(0);

		ImGuiUpdate();

		Meduza::Frame();

		if (!Meduza::IsActive())
			m_sandboxRun = false;
	}

	Meduza::Destroy();
}

void Sandbox::ImGuiUpdate()
{
	ImGui::Begin("Meduza Menu");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	if (ImGui::CollapsingHeader("Editor Style"))
	{
		if (ImGui::Button("Classic"))
		{
			ImGui::StyleColorsClassic();
		}
		ImGui::SameLine();

		if (ImGui::Button("Dark"))
		{
			ImGui::StyleColorsDark();
		}
		ImGui::SameLine();

		if (ImGui::Button("Light"))
		{
			ImGui::StyleColorsLight();
		}
	}
	ImGui::Text("Clear Colour");
	ImGui::ColorEdit3("Colour", (float*)&m_colour);
	ImGui::End();
}
