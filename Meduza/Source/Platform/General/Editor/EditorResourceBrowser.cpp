#include "MePCH.h"
#include "Platform/General/Editor/EditorResourceBrowser.h"

#include "MeduzaIncluder.h"

#include "Platform/General/Resources/MeshBase.h"
#include "Platform/General/Resources/ShaderBase.h"

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
		std::string name;

		switch (r.second->GetType())
		{
			case Resources::ResourceType::Audio:
				name.append("[Audio]   ");
			break;
			case Resources::ResourceType::Mesh:
				name.append("[Mesh]    ");
			break;
			case Resources::ResourceType::Script:
				name.append("[Script]  ");
				break;
			case Resources::ResourceType::Shader:
				name.append("[Shader]  ");
				break;
			case Resources::ResourceType::Texture:
				name.append("[Texture] ");
				break;
			default:
				name.append("[Unknow]  ");
				break;
		}

		name.append(r.second->GetFileName());

		bool open = ImGui::TreeNodeEx(name.c_str(), treeNodeFlags);
		if (open)
		{
			ImGui::Text("Resource ID : %u", r.second->GetID());
			ImGui::Text("Resource Name : %s", r.second->GetFileName().c_str());
			if (!r.second->GetPath().empty())
			{
				ImGui::Text("File : %s", r.second->GetPath().c_str());
			}

			if (r.second->GetType() == Resources::ResourceType::Mesh)
			{
				Resources::MeshBase* mesh = static_cast<Resources::MeshBase*>(r.second);
				ImGui::Text("Vertices : %i", mesh->GetVerticesSize());
				ImGui::Text("Indices : %i", mesh->GetIndicesSize());
			}
			
			ImGui::TreePop();
		}
	}

	ImGui::End();
}
