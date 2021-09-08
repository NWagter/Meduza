#include "MePCH.h"

#include "Platform/General/Editor/EditorEntityEditor.h"
#include "ECS/EntityManager.h"

#include "Platform/General/Editor/EditorEntityHierarchy.h"

#include "Core/Components/TransformComponent.h"
#include "Core/Components/RenderComponent.h"
#include "Core/Components/CameraComponent.h"
#include "Core/Components/PhysicsComponent.h"

#include "Platform/General/ShaderLibrary.h"

#include "Platform/General/Events/EventSystem.h"

#include "Platform/General/Editor/EditorHelper.h"


Me::Editor::EntityEditor::EntityEditor(EntityHierarchy& a_entHierarchy)
{
    m_hierarchy = &a_entHierarchy;
}

Me::Editor::EntityEditor::~EntityEditor()
{

}

template<typename T, typename Func>
static void DrawComponent(Me::EntityManager* a_eManager, const std::string a_name, EntityID a_entity, Func a_function, bool a_removeable = true)
{
    const ImGuiTreeNodeFlags treeNodeFlags =    ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | 
                                                ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap;
                                                
    auto component = a_eManager->GetComponent<T>(a_entity);

    if(component != nullptr)
    {
        bool removeComponent = false;

        bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, a_name.c_str());
        if(a_removeable)
        {
            ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
            if(ImGui::Button("...", ImVec2{20,20}))
            {
                ImGui::OpenPopup("Component Settings");
            }

            if(ImGui::BeginPopup("Component Settings"))
            {
                if(ImGui::MenuItem("Remove Component"))
                {
                    removeComponent = true;
                }

                ImGui::EndPopup();
            }

        }

        if(open)
        {
            a_function(*component);
            ImGui::TreePop();
        }

        if(removeComponent)
        {
            a_eManager->RemoveComponent<T>(a_entity);
        }
    }
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
        DrawComponent<TagComponent>(eManager, "Tag Component", m_selectedEntity, [](auto& a_comp)
        {
            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), a_comp.m_tag.c_str());
            if(ImGui::InputText("##Tag", buffer, sizeof(buffer)))
            {
                a_comp.m_tag = std::string(buffer);
            }

        }, false);

        DrawComponent<TransformComponent>(eManager, "Transform Component", m_selectedEntity, [](auto& a_comp)
        {
            bool isStatic = a_comp.m_isStatic;
            ImGui::Checkbox("Static", &isStatic);
            a_comp.m_isStatic = isStatic;

            Helper::EditorHelper::DrawVec3Prop("Position", a_comp.m_translation);
            Helper::EditorHelper::DrawVec3Prop("Rotation", a_comp.m_rotation);
            Helper::EditorHelper::DrawVec3Prop("Scale", a_comp.m_scale);
        }, false);

        DrawComponent<RenderComponent>(eManager, "Render Component", m_selectedEntity, [](auto& a_comp)
        {
            ImGui::ColorEdit4("Colour", a_comp.m_colour.m_colour);
        });

        DrawComponent<CameraComponent>(eManager, "Camera Component", m_selectedEntity, [](auto& a_comp)
        {
            const char* projectionStrings[] = { "Orthographic", "Perspective"};
            const char* currentProjectionString = projectionStrings[int(a_comp.m_cameraType)];

            if(ImGui::BeginCombo("Projection", currentProjectionString))
            {
                for(int i = 0; i < 2;i++)
                {
                    bool isSelected = currentProjectionString == projectionStrings[i];

                    if(ImGui::Selectable(projectionStrings[i], isSelected))
                    {
                        currentProjectionString = projectionStrings[i];
                        a_comp.m_cameraType = CameraType(i);
                    }

                    if(isSelected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }

            if(a_comp.m_cameraType == CameraType::Perspective)
            {
                Helper::EditorHelper::DrawVec2Prop("Size", a_comp.m_size);
            }else if(a_comp.m_cameraType == CameraType::Orthographic)
            {
                ImGui::DragFloat("Scale", &a_comp.m_orthoScale);
            }

            ImGui::DragFloat("Near", &a_comp.m_near);
            ImGui::DragFloat("Far", &a_comp.m_far);
        });

        DrawComponent<Physics::PhysicsComponent>(eManager, "Physics Component", m_selectedEntity, [](auto& a_comp)
        {

        });
    }

    if(ImGui::Button("Add Component"))
    {
        ImGui::OpenPopup("AddComponent");
    }

    if(ImGui::BeginPopup("AddComponent"))
    {
        if(ImGui::MenuItem("RenderComponent"))
        {
            auto rComp = new RenderComponent();
            rComp->m_mesh = Mesh(Primitives::Quad);

            Me::Shader shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/LitColour_Shader.hlsl");
            if(shader == 0)
            {      
                shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/LitColour_Shader.glsl");
            }

            rComp->m_shader = shader;

            eManager->AddComponent(m_selectedEntity, rComp);
            ImGui::CloseCurrentPopup();
        }
        if(ImGui::MenuItem("Camera Component"))
        {
            auto cComp = new CameraComponent();
            cComp->m_size = Event::EventSystem::GetEventSystem()->ScreenSize();

            eManager->AddComponent(m_selectedEntity, cComp);
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

	ImGui::End();
}