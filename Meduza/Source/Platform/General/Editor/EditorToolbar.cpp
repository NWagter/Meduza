#include "MePCH.h"
#include "Platform/General/Editor/EditorToolbar.h"

#include "ECS/EntityManager.h"

Me::Editor::EditorToolbar::EditorToolbar()
{

}

Me::Editor::EditorToolbar::~EditorToolbar()
{
    
}

void Me::Editor::EditorToolbar::Draw()
{
    EntityManager* eManager = EntityManager::GetEntityManager();

    if(ImGui::BeginMainMenuBar())
    {
        if(ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("New"))
            {
                for(auto ent: eManager->GetEntities())
                {
                    eManager->DestroyEntity(ent.first);
                }
            }
            if(ImGui::MenuItem("Exit"))
            {

            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}