#include "MePCH.h"
#include "Platform/General/Editor/EditorToolbar.h"

#include "ECS/EntityManager.h"

#include "Core/Components/TransformComponent.h"
#include "Core/Components/RenderComponent.h"

#include "Platform/General/ShaderLibrary.h"

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
        if(ImGui::BeginMenu("Create"))
        {
            if(ImGui::BeginMenu("3D Object"))
            {
                bool createMesh = false;
                Primitives primitive = Primitives::Cube;
                if(ImGui::Button("Cube"))
                {
                    createMesh = true;
                    primitive = Primitives::Cube;
                }
                if(ImGui::Button("Sphere"))
                {
                    createMesh = true;
                    primitive = Primitives::Sphere;
                }
                if(ImGui::Button("Plane"))
                {
                    createMesh = true;
                    primitive = Primitives::Plane;
                }
                if(ImGui::Button("Quad"))
                {
                    createMesh = true;
                    primitive = Primitives::Quad;
                }

                if(createMesh)
                {
                                        
                    EntityID ent = eManager->CreateEntity();
                    eManager->AddComponent<TransformComponent>(ent);

                    auto rComp = new RenderComponent();
                    rComp->m_mesh = Mesh(primitive);

                    Me::Shader shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/LitColour_Shader.hlsl");
                    if(shader == 0)
                    {      
                        shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/LitColour_Shader.glsl");
                    }

                    rComp->m_shader = shader;

                    eManager->AddComponent(ent, rComp);
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}