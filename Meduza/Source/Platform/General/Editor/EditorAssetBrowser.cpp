#include "MePCH.h"
#include "Platform/General/Editor/EditorAssetBrowser.h"

#include "MeduzaIncluder.h"

#include "Platform/General/Resources/Resource.h"

Me::Editor::EditorAssetBrowser::EditorAssetBrowser()
{
	for (uint8_t i = 0; i < uint8_t(Resources::ResourceType::LAST); i++)
	{
		m_filter[uint8_t(i)] = true;
	}
}

Me::Editor::EditorAssetBrowser::~EditorAssetBrowser()
{
}

void Me::Editor::EditorAssetBrowser::Update(float)
{
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

		ImGui::End();
	}
	ImGui::End();
}
