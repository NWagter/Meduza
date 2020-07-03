#include "mePch.h"
#include "Editor/EditorMenu.h"

#include "Platform/General/Window/Window.h"
#include "Platform/General/Gfx/Renderer.h"
#include "Platform/General/Utils/MeduzaHelper.h"

#include "Editor/EditorStats.h"


meduza::editor::EditorMenu::EditorMenu(renderer::Renderer& a_renderer, Window& a_window)
{
	m_window = &a_window;
	m_renderer = &a_renderer;

	m_api = { "OpenGL", "DirectX12" };

	m_currentAPI = int(meduza::MeduzaHelper::ms_activeAPI);

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

		int currentIndex = m_currentAPI;
		bool apiChange = false;
		if (ImGui::BeginMenu("Meduza"))
		{
			if (ImGui::BeginCombo("API", m_api.at(m_currentAPI).c_str()))
			{
				const char* current_item = NULL;
				for (int n = 0; n < m_api.size(); n++)
				{
					bool is_selected = (current_item == m_api.at(n).c_str()); // You can store your selection however you want, outside or inside your objects

					if (ImGui::Selectable(m_api.at(n).c_str(), is_selected))
					{
						current_item = m_api.at(n).c_str();
						if (n != m_currentAPI)
						{
							m_currentAPI = n;
							apiChange = true;
						}
					}
				}
				ImGui::EndCombo();
			}
			ImGui::Checkbox("Draw Stats", &m_drawStats);
			ImGui::EndMenu();
		}

		std::string api = "API : ";
		api.append(m_api.at(currentIndex));
		float i = ImGui::GetWindowSize().x;
		ImGui::SameLine(i - float(api.length() * ImGui::GetFontSize()));
		ImGui::Text(api.c_str());

		ImGui::EndMainMenuBar();

		if (apiChange)
		{
			ChangeAPI();
		}
	}

	if (m_drawStats)
	{
		m_editorStats->Update(a_dt);
	}
}

void meduza::editor::EditorMenu::ChangeAPI()
{
	meduza::MeduzaHelper::ms_activeAPI = meduza::API(m_currentAPI);
	m_changeAPI = true;
}
