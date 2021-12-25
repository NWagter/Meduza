#include "MePCH.h"
#include "Platform/General/Editor/EditorAssetBrowser.h"

#include "MeduzaIncluder.h"
#include "Platform/General/Resources/Resource.h"

Me::Editor::EditorAssetBrowser::EditorAssetBrowser() : m_reloadTime(0.5f)
{
	for (uint8_t i = 0; i < uint8_t(Resources::ResourceType::LAST); i++)
	{
		m_filter[uint8_t(i)] = true;
	}

	m_browserData = Files::BrowseData();
	m_browserPath = "Assets";
	Files::Windows::FileSystem::GetFilesOfType(m_browserData, Files::FileType::Any, false, m_browserPath);
	m_timer = 0;
}

Me::Editor::EditorAssetBrowser::~EditorAssetBrowser()
{
}

void Me::Editor::EditorAssetBrowser::Update(float a_dt)
{
	if (m_timer >= m_reloadTime)
	{
		m_browserData.Clear();
		Files::Windows::FileSystem::GetFilesOfType(m_browserData, Files::FileType::Any, false, m_browserPath);
		m_timer = 0;
	}

	m_timer += a_dt;
}

void Me::Editor::EditorAssetBrowser::Draw()
{
	Resources::ResourceLibrary* rLibrary = Resources::ResourceLibrary::GetInstance();
	if (ImGui::Begin("AssetBrowser"))
	{
		ImGuiID assetBrowserDockSpace;
		assetBrowserDockSpace = ImGui::GetID("Asset_Space");
		ImGui::DockSpace(assetBrowserDockSpace, ImVec2(0,0), ImGuiDockNodeFlags_NoTabBar);

		ImGui::SetNextWindowDockID(assetBrowserDockSpace);
		ImGui::Begin("##AssetBrowser");

		if (ImGui::Begin("Filters ##Assets"))
		{
			for (uint8_t i = 0; i < uint8_t(Resources::ResourceType::LAST); i++)
			{
				ImGui::Checkbox(Resources::gs_resourceTypes[uint8_t(i)], &m_filter[uint8_t(i)]);
			}
			ImGui::End();
		}

		if (m_browserData.m_path != "Assets")
		{
			if (ImGui::Button("../"))
			{
				m_browserPath = Files::Windows::FileSystem::GetParentPath(m_browserPath);
				m_browserData.Clear();
				Files::Windows::FileSystem::GetFilesOfType(m_browserData, Files::FileType::Any, false, m_browserPath);
			}
		}

		for (auto folder : m_browserData.m_folders)
		{
			if (ImGui::Button(folder.c_str()))
			{
				m_browserPath.append("/");
				m_browserPath.append(folder);
				m_browserData.Clear();
				Files::Windows::FileSystem::GetFilesOfType(m_browserData, Files::FileType::Any, false, m_browserPath);
				break;
			}
		}

		for (auto file : m_browserData.m_files)
		{
			if (!m_filter[uint8_t(file.m_type)])
			{
				continue;
			}

			ImGui::Text(file.m_name.c_str());
		}

		ImGui::End();
	}
	ImGui::End();
}
