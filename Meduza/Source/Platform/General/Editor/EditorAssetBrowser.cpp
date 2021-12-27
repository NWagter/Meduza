#include "MePCH.h"
#include "Platform/General/Editor/EditorAssetBrowser.h"

#include "Platform/General/Editor/EditorHelper.h"
#include "MeduzaIncluder.h"
#include "Platform/General/Resources/Resource.h"

#include "Platform/General/Graphics/RenderLayer.h"

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
		if (ImGui::BeginDragDropTarget())
		{
			if (ImGuiPayload const* payLoad = ImGui::AcceptDragDropPayload("ENTITY_HIERARCHY_ITEM"))
			{
				Helper::EntityPayload* payload = (Helper::EntityPayload*)(payLoad->Data);

				if (!m_browserPath.empty())
				{
					Me::Serialization::Serializer::GetInstance()->SerializeEntity(Files::FileSystem::CreateNewFile(payload->m_entityName, m_browserPath), payload->m_entityID);
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

		Me::GFX_API const api = Renderer::RenderLayer::GetAPI();

		ImTextureID folderTextureID = 0;
		ImTextureID fileTextureID = 0;

		if (api == Me::GFX_API::OpenGL)
		{
			folderTextureID = (void*)(static_cast<Resources::GL::Texture*>(m_folderIcon)->GetTexture());
			fileTextureID = (void*)(static_cast<Resources::GL::Texture*>(m_fileIcon)->GetTexture());
		}
		else if (api == Me::GFX_API::DX12)
		{	
			auto folderTexture = static_cast<Resources::Dx12::Texture*>(m_folderIcon);
			auto fileTexture = static_cast<Resources::Dx12::Texture*>(m_fileIcon);

			CD3DX12_GPU_DESCRIPTOR_HANDLE folderHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(folderTexture->GetTexture().m_srv->GetGPUDescriptorHandleForHeapStart());
			folderHandle.Offset(folderTexture->GetTexture().m_srvOffset, folderTexture->GetTexture().m_handleIncrementer);

			CD3DX12_GPU_DESCRIPTOR_HANDLE fileHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(fileTexture->GetTexture().m_srv->GetGPUDescriptorHandleForHeapStart());
			fileHandle.Offset(fileTexture->GetTexture().m_srvOffset, fileTexture->GetTexture().m_handleIncrementer);

			folderTextureID = (ImTextureID)folderHandle.ptr;
			fileTextureID = (ImTextureID)fileHandle.ptr;
		}

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
				break;
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

			ImGui::Text(file->m_name.c_str());

			ImGui::NextColumn();
			ImGui::PopID();
		}
		ImGui::Columns(1);

		ImGui::End();
	}
	ImGui::End();
}
