#include "MePCH.h"
#include "Platform/General/Editor/EditorResourceBrowser.h"

#include "MeduzaIncluder.h"

#include "Platform/General/Resources/Resource.h"

Me::Editor::EditorResourceBrowser::EditorResourceBrowser()
{
}

Me::Editor::EditorResourceBrowser::~EditorResourceBrowser()
{
}

void Me::Editor::EditorResourceBrowser::Update(float)
{
}

void Me::Editor::EditorResourceBrowser::Draw()
{
	Resources::ResourceLibrary* rLibrary = Resources::ResourceLibrary::GetInstance();
	ImGui::Begin("Resource Browser");    
	
	const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_AllowItemOverlap;

	for (auto r : rLibrary->GetResources())
	{
		bool open = ImGui::TreeNodeEx(r.second->GetFileName().c_str(), treeNodeFlags);
		if (open)
		{
			ImGui::Text("Resource ID : %u", r.second->GetID());
			ImGui::Text("Resource Name : %s", r.second->GetFileName().c_str());

			switch (r.second->GetType())
			{
			case Resources::ResourceType::Mesh:
				ImGui::Text("Resource Type : Mesh");
				break;
			case Resources::ResourceType::Shader:
				ImGui::Text("Resource Type : Shader");
				break;
			case Resources::ResourceType::Texture:
				ImGui::Text("Resource Type : Texture");
				break;
			case Resources::ResourceType::Audio:
				ImGui::Text("Resource Type : Audio");
				break;
			case Resources::ResourceType::Script:
				ImGui::Text("Resource Type : Script");
				break;
			default:
				ImGui::Text("Resource Type : Unkown");
				break;
			}

			if (!r.second->GetPath().empty())
			{
				ImGui::Text("File : %s", r.second->GetPath().c_str());
			}
			ImGui::TreePop();
		}
	}

	ImGui::End();
}
