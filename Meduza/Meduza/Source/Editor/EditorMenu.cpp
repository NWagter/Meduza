#include "mePch.h"
#include "Editor/EditorMenu.h"

#include "Platform/General/Window/Window.h"
#include "Platform/General/Gfx/Renderer.h"

#include "Editor/EditorStats.h"

meduza::editor::EditorMenu::EditorMenu(renderer::Renderer& a_renderer, Window& a_window)
{
	m_window = &a_window;
	m_renderer = &a_renderer;

	m_editorStats = new EditorStats(a_renderer);
}

meduza::editor::EditorMenu::~EditorMenu()
{
	delete m_editorStats;
}

void meduza::editor::EditorMenu::Update(const float a_dt)
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::Button("Exit"))
			{
				m_window->Close();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Meduza"))
		{
			ImGui::Checkbox("Draw Stats", &m_drawStats);
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	if (m_drawStats)
	{
		m_editorStats->Update(a_dt);
	}
}
