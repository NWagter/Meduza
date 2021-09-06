#include "MePCH.h"

#include "Platform/General/Editor/EditorEntityHierarchy.h"
#include "ECS/EntityManager.h"
#include "Core/Components/TransformComponent.h"

Me::Editor::EntityHierarchy::EntityHierarchy()
{

}

Me::Editor::EntityHierarchy::~EntityHierarchy()
{

}

bool DrawEnt(EntityID& a_selected, EntityID a_ent, std::string a_tag, bool& a_shouldDelete)
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
		EntityID selected = m_selectedEntity;
		bool shouldDelete = false; 
		if(DrawEnt(selected, ent.first, eManager->GetComponent<TagComponent>(ent.first)->m_tag, shouldDelete))
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