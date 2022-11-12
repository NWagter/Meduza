#include "MePCH.h"
#include "Platform/General/Editor/EditorAssetBrowser.h"

#include "Core/Project/ProjectManager.h"

#include "Platform/General/Editor/EditorHelper.h"
#include "MeduzaIncluder.h"
#include "Platform/General/Resources/Resource.h"

#include "Platform/General/Graphics/RenderLayer.h"

#include "Platform/General/Resources/Texture.h"
#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/Helper/Helper.h"
#endif // PLATFORM_WINDOWS


Me::Editor::EditorAssetBrowser::EditorAssetBrowser() : m_reloadTime(0.5f), m_padding(16.0f)
{
	for (uint8_t i = 0; i < uint8_t(Resources::ResourceType::LAST); i++)
	{
		m_filter[uint8_t(i)] = true;
	}

	m_browserData = Files::BrowseData();
	m_browserBase = m_browserPath = Project::ProjectManager::GetAssetBrowserPath();
	Files::Windows::FileSystem::GetFilesOfType(m_browserData, Files::FileType::Any, false, m_browserPath);
	m_timer = 0;

	m_thumbnailSize = 64.0f;

	LoadIcons();
}

Me::Editor::EditorAssetBrowser::~EditorAssetBrowser()
{
	m_browserData.Clear();
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

	ImTextureID folderTextureID;
	ImTextureID fileTextureID;

	auto folderTexture = rLibrary->GetResource<Resources::TextureBase>(m_folderTextureID);
	auto fileTexure = rLibrary->GetResource<Resources::TextureBase>(m_fileTextureID);

	if (folderTexture && fileTexure)
	{
		Me::GFX_API const api = Renderer::RenderLayer::GetAPI();
		if (api == Me::GFX_API::OpenGL)
		{
			folderTextureID = (void*)((uint64_t)(static_cast<Resources::GL::Texture*>(folderTexture)->GetTexture()));
			fileTextureID = (void*)((uint64_t)(static_cast<Resources::GL::Texture*>(fileTexure)->GetTexture()));
		}
		else if (api == Me::GFX_API::DX12)
		{
#ifdef PLATFORM_WINDOWS
			ME_CORE_ASSERT_M(false, "No implementation yet for DX12");
			return;
#endif // PLATFORM_WINDOWS
		}
	}
	else
	{
		LoadIcons();
	}

	if (ImGui::Begin("AssetBrowser"))
	{
		if (m_browserPath.empty() || m_browserBase != Project::ProjectManager::GetAssetBrowserPath())
		{
			m_browserBase = m_browserPath = Project::ProjectManager::GetAssetBrowserPath();
			ImGui::End();
			return;
		}

		ImGuiID assetBrowserDockSpace;
		assetBrowserDockSpace = ImGui::GetID("Asset_Space");
		ImGui::DockSpace(assetBrowserDockSpace, ImVec2(0,0), ImGuiDockNodeFlags_NoTabBar);
		if (ImGui::BeginDragDropTarget())
		{
			if (ImGuiPayload const* payLoad = ImGui::AcceptDragDropPayload("ENTITY_HIERARCHY_ITEM"))
			{
				Helper::EntityPayload* payload = (Helper::EntityPayload*)(payLoad->Data);

				if (!m_browserPath.empty())
				{
					std::string file = payload->m_entityName;
					file.append(".prefab");
					Me::Serialization::Serializer::GetInstance()->SerializeEntity(Files::FileSystem::CreateNewFile(file, m_browserPath), payload->m_entityID);
				}
			}

			ImGui::EndDragDropTarget();
		}

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

		if (m_browserData.m_path != Project::ProjectManager::GetAssetBrowserPath())
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

		for (auto folder : m_browserData.m_folders)
		{
			ImGui::PushID(folder.c_str());
			float canvasWidth = ImGui::GetWindowContentRegionWidth();
			if (ImGui::ImageButton(folderTextureID, { m_thumbnailSize, m_thumbnailSize }))
			{
				m_browserPath.append("/");
				m_browserPath.append(folder);
				m_browserData.Clear();
				Files::Windows::FileSystem::GetFilesOfType(m_browserData, Files::FileType::Any, false, m_browserPath);
				ImGui::NextColumn();
				ImGui::PopID();
				m_showOptions = false;
				break;
			}
			if (ImGui::BeginPopupContextItem())
			{
				if (ImGui::MenuItem("Open Folder"))
				{
					std::string folderToOpen = m_browserPath;
					folderToOpen.append("/");
					folderToOpen.append(folder);
					Files::Windows::FileSystem::OpenFolder(folderToOpen);
				}
				ImGui::EndPopup();
			}

			ImGui::Text(folder.c_str());
			ImGui::NextColumn();
			ImGui::PopID();
		}

		for (auto file : m_browserData.m_files)
		{
			if (!m_filter[uint8_t(file->m_type)])
			{
				continue;
			}

			ImGui::PushID(file->m_name.c_str()); 
			ImGui::ImageButton(fileTextureID, { m_thumbnailSize, m_thumbnailSize });
			if (ImGui::BeginDragDropSource())
			{
				ImGui::SetDragDropPayload("ASSET_ITEM", file, sizeof(Files::MeduzaFile), ImGuiCond_Always);
				ImGui::EndDragDropSource();
			}
			if (ImGui::BeginPopupContextItem())
			{
				if (ImGui::MenuItem("Delete File"))
				{
					Files::FileSystem::DeleteAsset(file->m_path);
				}
				ImGui::EndPopup();
			}

			ImGui::Text(file->m_name.c_str());
			ImGui::NextColumn();
			ImGui::PopID();
		}
		ImGui::Columns(1);

		ImGui::End();
	}
	ImGui::End();
}

void Me::Editor::EditorAssetBrowser::LoadIcons()
{
	m_folderTextureID = Resources::ResourceLibrary::GetInstance()->LoadResource<Resources::TextureBase>("Resources/Textures/Icons/AssetBrowser/FolderIcon.png")->GetID();
	m_fileTextureID = Resources::ResourceLibrary::GetInstance()->LoadResource<Resources::TextureBase>("Resources/Textures/Icons/AssetBrowser/FileIcon.png")->GetID();
}