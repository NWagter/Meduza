#include "MePCH.h"
#include "Platform/General/Editor/EditorAssetBrowser.h"

#include "MeduzaIncluder.h"
#include "Platform/General/Resources/Resource.h"

#include "Platform/General/Resources/Texture.h"
#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/Resources/Texture.h"
#include "Platform/Windows/Helper/Helper.h"
#endif // PLATFORM_WINDOWS


Me::Editor::EditorAssetBrowser::EditorAssetBrowser() : m_reloadTime(0.5f), m_padding(16.0f)
{
	for (uint8_t i = 0; i < uint8_t(Resources::ResourceType::LAST); i++)
	{
		m_filter[uint8_t(i)] = true;
	}

	m_browserData = Files::BrowseData();
	m_browserPath = "Assets";
	Files::Windows::FileSystem::GetFilesOfType(m_browserData, Files::FileType::Any, false, m_browserPath);
	m_timer = 0;

	m_thumbnailSize = 64.0f;

	m_folderIcon = Resources::ResourceLibrary::GetInstance()->LoadResource<Resources::TextureBase>("Resources/Textures/Icons/AssetBrowser/FolderIcon.png");
	m_fileIcon = Resources::ResourceLibrary::GetInstance()->LoadResource<Resources::TextureBase>("Resources/Textures/Icons/AssetBrowser/FileIcon.png");
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

		ImGui::DragFloat("Scale", &m_thumbnailSize, 1.0f, 4.0f, 256.0f);

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

		float cellSize = m_thumbnailSize + m_padding;
		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columns = int(panelWidth / cellSize);

		ImGui::Columns(columns < 1 ? 1 : columns, 0, false);

		Resources::GL::Texture* folderIcon = static_cast<Resources::GL::Texture*>(m_folderIcon);
		Resources::GL::Texture* fileIcon = static_cast<Resources::GL::Texture*>(m_fileIcon);

		for (auto folder : m_browserData.m_folders)
		{
			ImGui::PushID(folder.c_str());
			float canvasWidth = ImGui::GetWindowContentRegionWidth();
			if (ImGui::ImageButton((void*)(folderIcon->GetTexture()), { m_thumbnailSize, m_thumbnailSize }))
			{
				m_browserPath.append("/");
				m_browserPath.append(folder);
				m_browserData.Clear();
				Files::Windows::FileSystem::GetFilesOfType(m_browserData, Files::FileType::Any, false, m_browserPath);
				break;
			}
			ImGui::Text(folder.c_str());
			ImGui::NextColumn();
			ImGui::PopID();
		}

		for (auto file : m_browserData.m_files)
		{
			if (!m_filter[uint8_t(file.m_type)])
			{
				continue;
			}
			ImGui::PushID(file.m_name.c_str());
			if (ImGui::ImageButton((void*)(fileIcon->GetTexture()), { m_thumbnailSize, m_thumbnailSize }))
			{

			}
			ImGui::Text(file.m_name.c_str());
			ImGui::NextColumn();
			ImGui::PopID();
		}
		ImGui::Columns(1);

		ImGui::End();
	}
	ImGui::End();
}
