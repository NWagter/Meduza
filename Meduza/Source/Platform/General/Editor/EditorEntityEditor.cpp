#include "MePCH.h"

#include "Platform/General/Editor/EditorEntityEditor.h"
#include "ECS/EntityManager.h"

#include "Platform/General/Editor/EditorEntityHierarchy.h"

#include "Core/Components/TransformComponent.h"
#include "Core/Components/RenderComponent.h"


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

            if(c == TransformComponent::s_componentID)
            {    
                auto tC = eManager->GetComponent<TransformComponent>(m_selectedEntity);
                if(tC != nullptr)
                {
                    bool isStatic = tC->m_isStatic;
                    ImGui::Checkbox("Static", &isStatic);
                    tC->m_isStatic = isStatic;

                    ImGui::InputFloat3("Position", tC->m_translation.m_xyz);
                    ImGui::InputFloat3("Rotation", tC->m_rotation.m_xyz);
                    ImGui::InputFloat3("Scale", tC->m_scale.m_xyz);
                }
            }
            if(c == RenderComponent::s_componentID)
            {    
                auto rC = eManager->GetComponent<RenderComponent>(m_selectedEntity);
                
                if(rC != nullptr)
                {   
                    ImGui::ColorEdit4("Colour", rC->m_colour.m_colour);
                }
            }
        }
    }

	ImGui::End();
}