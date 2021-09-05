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

bool DrawEnt(EntityID& a_selected, std::string a_tag)
{
	bool isSelected = false;
	ImGui::Selectable(a_tag.c_str(), &isSelected);

	return isSelected;
}

void Me::Editor::EntityHierarchy::Draw()
{    
	auto eManager = EntityManager::GetEntityManager();
	
	ImGui::Begin("Entities");

	if(ImGui::Button("Create Entity"))
	{
		EntityID ent = eManager->CreateEntity();
		eManager->AddComponent<TransformComponent>(ent);
	}

	for(auto ent : eManager->GetEntities())
	{
		EntityID selected = m_selectedEntity; 
		if(DrawEnt(selected, eManager->GetComponent<TagComponent>(ent.first)->m_tag))
		{
			m_selectedEntity = ent.first;
		}	
		
	}
	ImGui::End();
}

Me::EntityID Me::Editor::EntityHierarchy::GetSelected()
{
	return m_selectedEntity;
}