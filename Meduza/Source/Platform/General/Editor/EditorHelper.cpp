#include "MePCH.h"

#include "Platform/General/Editor/EditorHelper.h"

bool Me::Editor::Helper::EditorHelper::DrawVector2Prop(std::string const& a_label, Me::Math::Vector2& a_value, float const a_resetValue, float const a_columnWidth)
{
    bool changed = false;

    ImGui::PushID(a_label.c_str());
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, a_columnWidth);
    ImGui::Text(a_label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0.0f, 0.0f});

    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = {lineHeight + 3.0f, lineHeight};

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.9f, 0.2f, 0.15f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
    
    if(ImGui::Button("X", buttonSize))
    {
        a_value.m_x = a_resetValue;
        changed = true;
    }
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    if(ImGui::DragFloat("##X", &a_value.m_x, 0.1f, 0.0f, 0.0f, "%.2f"))
    {
        changed = true;
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.3f, 0.8f, 0.3f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
    
    if(ImGui::Button("Y", buttonSize))
    {
        a_value.m_y = a_resetValue;
        changed = true;
    }
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    if (ImGui::DragFloat("##Y", &a_value.m_y, 0.1f, 0.0f, 0.0f, "%.2f")) 
    { 
        changed = true; 
    }
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();
    ImGui::Columns(1);
    ImGui::PopID();

    return changed;
}
bool Me::Editor::Helper::EditorHelper::DrawVector3Prop(std::string const& a_label, Me::Math::Vector3& a_value, float const a_resetValue, float const a_columnWidth)
{
    bool changed = false;

    ImGui::PushID(a_label.c_str());
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, a_columnWidth);
    ImGui::Text(a_label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0.0f, 0.0f});

    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = {lineHeight + 3.0f, lineHeight};

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.9f, 0.2f, 0.15f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
    
    if(ImGui::Button("X", buttonSize))
    {
        a_value.m_x = a_resetValue;
        changed = true;
    }
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    if (ImGui::DragFloat("##X", &a_value.m_x, 0.1f, 0.0f, 0.0f, "%.2f"))
    {
        changed = true;
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.3f, 0.8f, 0.3f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
    
    if(ImGui::Button("Y", buttonSize))
    {
        a_value.m_y = a_resetValue;
        changed = true;
    }
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    if (ImGui::DragFloat("##Y", &a_value.m_y, 0.1f, 0.0f, 0.0f, "%.2f"))
    {
        changed = true;
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.2f, 0.35f, 0.9f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
    
    if(ImGui::Button("Z", buttonSize))
    {
        a_value.m_z = a_resetValue;
        changed = true;
    }
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    if (ImGui::DragFloat("##Z", &a_value.m_z, 0.1f, 0.0f, 0.0f, "%.2f"))
    {
        changed = true;
    }
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();
    ImGui::Columns(1);
    ImGui::PopID();

    return changed;
}
bool Me::Editor::Helper::EditorHelper::DrawVector4Prop(std::string const& a_label, Me::Math::Vector4& a_value, float const a_resetValue, float const a_columnWidth)
{
    bool changed = false;

    ImGui::PushID(a_label.c_str());
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, a_columnWidth);
    ImGui::Text(a_label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(4, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0.0f, 0.0f});

    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = {lineHeight + 3.0f, lineHeight};

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.9f, 0.2f, 0.15f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
    
    if(ImGui::Button("X", buttonSize))
    {
        a_value.m_x = a_resetValue;
        changed = true;
    }
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    if(ImGui::DragFloat("##X", &a_value.m_x, 0.1f, 0.0f, 0.0f, "%.2f"))
    {
        changed = true;
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.3f, 0.8f, 0.3f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
    
    if(ImGui::Button("Y", buttonSize))
    {
        a_value.m_y = a_resetValue;
        changed = true;
    }
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    if(ImGui::DragFloat("##Y", &a_value.m_y, 0.1f, 0.0f, 0.0f, "%.2f"))
    {
        changed = true;
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.2f, 0.35f, 0.9f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
    
    if(ImGui::Button("Z", buttonSize))
    {
        a_value.m_z = a_resetValue;
        changed = true;
    }
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    if(ImGui::DragFloat("##Z", &a_value.m_z, 0.1f, 0.0f, 0.0f, "%.2f"))
    {
        changed = true;
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.2f, 0.35f, 0.9f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
    
    if(ImGui::Button("W", buttonSize))
    {
        a_value.m_z = a_resetValue;
        changed = true;
    }
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    if(ImGui::DragFloat("##W", &a_value.m_w, 0.1f, 0.0f, 0.0f, "%.2f"))
    {
        changed = true;
    }
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();
    ImGui::Columns(1);
    ImGui::PopID();

    return changed;
}