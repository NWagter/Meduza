#include "MePCH.h"
#include "Platform/General/Editor/EditorToolbar.h"

Me::Editor::EditorToolbar::EditorToolbar()
{

}

Me::Editor::EditorToolbar::~EditorToolbar()
{
    
}

void Me::Editor::EditorToolbar::Draw()
{
    if(ImGui::BeginMainMenuBar())
    {
        if(ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("New"))
            {

            }
            if(ImGui::MenuItem("Load..."))
            {

            }
            if(ImGui::MenuItem("Save..."))
            {

            }
            if(ImGui::MenuItem("Exit"))
            {

            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}