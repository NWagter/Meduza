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

void DrawEnt(EntityID& a_selected, std::pair<EntityID, EntityFilter> a_ent)
{
	std::string entID = std::to_string(a_ent.first);
	bool isSelected = false;
	ImGui::Selectable(entID.c_str(), &isSelected);

	if(isSelected)
	{
		a_selected = a_ent.first;
	}
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
		DrawEnt(selected, ent);	

		if(selected != m_selectedEntity)
		{
			m_selectedEntity = selected;
		}
		
	}
	ImGui::End();
}

Me::EntityID Me::Editor::EntityHierarchy::GetSelected()
{
	return m_selectedEntity;
}