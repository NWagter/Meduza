#include "MePCH.h"

#include "Platform/General/Editor/EditorEntityHierarchy.h"
#include "ECS/EntityManager.h"

#include "Core/Serialization/Serializer.h"
#include "Platform/General/Window.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#include "Platform/Windows/FileSystem/FileSystem.h"
#endif

#include "Core/Components/TransformComponent.h"

Me::Editor::EntityHierarchy::EntityHierarchy(Me::Window& a_window)
{
    m_window = &a_window;
}

Me::Editor::EntityHierarchy::~EntityHierarchy()
{

}

bool DrawEnt(EntityID& a_selected, EntityID a_ent, std::string a_tag, bool& a_shouldDelete, Me::Window* a_window)
{
	bool isSelected = false;

	ImGui::PushID(a_ent);
	ImGui::Selectable(a_tag.c_str(), &isSelected);	
	ImGui::PopID();

	if(ImGui::BeginPopupContextItem())
	{
		if(ImGui::MenuItem("Destroy Entity"))
		{
			a_shouldDelete = true;
		}
		if(ImGui::MenuItem("Create Prefab Entity"))
		{               
			#ifdef PLATFORM_WINDOWS

			std::string filePath = Me::Files::Windows::FileSystem::SaveFile(
				"Meduza Prefab \0*.prefab*\0Prefab\0*.prefab\0",
					static_cast<Me::WindowsWindow*>(a_window)->GetWindowHandle());

			size_t pos = filePath.find("Assets"); //find location of word
			filePath.erase(0,pos); //delete everything prior to location found
			std::replace(filePath.begin(), filePath.end(), '\\', '/');

			if(!filePath.empty())
			{
				Me::Serialization::Serializer::GetInstance()->SerializeEntity(filePath, a_ent);
			}

			#endif
		}
		ImGui::EndPopup();
	}

	return isSelected;
}

void Me::Editor::EntityHierarchy::Draw()
{    
	auto eManager = EntityManager::GetEntityManager();
	
	ImGui::Begin("Entities");

	if(ImGui::BeginPopupContextWindow(0, 1, false))
	{
		if(ImGui::MenuItem("Create Entity"))
		{
			EntityID newEnt = eManager->CreateEntity("New Entity");
			eManager->AddComponent<TransformComponent>(newEnt);
		}

		ImGui::EndPopup();
	}

	for(auto ent : eManager->GetEntities())
	{
		if(eManager->GetComponent<EditorComponent>(ent.first) != nullptr)
		{
			continue;
		}
		EntityID selected = m_selectedEntity;
		bool shouldDelete = false; 
		TagComponent* tagComp = eManager->GetComponent<TagComponent>(ent.first);
		if(tagComp != nullptr && DrawEnt(selected, ent.first, tagComp->m_tag, shouldDelete, m_window))
		{
			m_selectedEntity = ent.first;
		}	

		if(shouldDelete)
		{
			eManager->DestroyEntity(ent.first);
			m_selectedEntity = 0;
		}
		
	}
	ImGui::End();
}

Me::EntityID Me::Editor::EntityHierarchy::GetSelected()
{
	return m_selectedEntity;
}