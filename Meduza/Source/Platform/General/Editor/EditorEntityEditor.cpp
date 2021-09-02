#include "MePCH.h"

#include "Platform/General/Editor/EditorEntityEditor.h"
#include "ECS/EntityManager.h"
#include "Core/Components/TransformComponent.h"

#include "Platform/General/Editor/EditorEntityHierarchy.h"


Me::Editor::EntityEditor::EntityEditor(EntityHierarchy& a_entHierarchy)
{
    m_hierarchy = &a_entHierarchy;
}

Me::Editor::EntityEditor::~EntityEditor()
{

}

void Me::Editor::EntityEditor::Draw()
{    
	auto eManager = EntityManager::GetEntityManager();
	
	ImGui::Begin("Entity Editor");

    ImGui::Checkbox("Locked", &m_locked);
    
    if(!m_locked)
    {
        m_selectedEntity = m_hierarchy->GetSelected();
    }

    if(m_selectedEntity > 0)
    {
        auto filter = eManager->GetEntities()[m_selectedEntity];
        auto names = eManager->GetComponentNames();
        for(auto c : filter)
        {
            ImGui::LabelText("", names[c].c_str());
        }
    }

	ImGui::End();
}