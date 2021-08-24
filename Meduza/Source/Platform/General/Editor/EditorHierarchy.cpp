#include "MePCH.h"

#include "Platform/General/Editor/EntityHierarchy.h"
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
			ME_CORE_LOG("Selected Entity : %i \n", (int)selected);
			m_selectedEntity = selected;
		}	

		if(m_selectedEntity > 0 && ent.first == m_selectedEntity)
		{
			auto filter = eManager->GetEntities()[m_selectedEntity];
			auto names = eManager->GetComponentNames();
			for(auto c : filter)
			{
				ImGui::LabelText("", names[c].c_str());
			}
		}	
	}
	ImGui::End();
}