#include "MePCH.h"
#include "Platform/General/Editor/EditorToolbar.h"

#include "ECS/EntityManager.h"

#include "Core/Components/TransformComponent.h"
#include "Core/Components/RenderComponent.h"

#include "Platform/General/ShaderLibrary.h"

#include "Core/Serialization/Serializer.h"

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
            if(ImGui::MenuItem("Save"))
            {
                Serialization::Serializer::GetInstance()->SerializeScene("test.xml");
            }
            if(ImGui::MenuItem("Load"))
            {
                Serialization::Serializer::GetInstance()->DeserializeScene("test.xml");
            }
            if(ImGui::MenuItem("Load MonkeyHead"))
            {
                Serialization::Serializer::GetInstance()->DeserializeScene("Assets/Scenes/MonkeyHeadScene.xml");
            }
            if(ImGui::MenuItem("Exit"))
            {

            }

            ImGui::EndMenu();
        }

        bool createMesh = false;
        Primitives primitive = Primitives::Cube;
        Shader shader = 0;

        if(ImGui::BeginMenu("Create"))
        {
            if(ImGui::BeginMenu("3D Object"))
            {
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
                    shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/LitColour_Shader.hlsl");
                    if(shader == 0)
                    {      
                        shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/LitColour_Shader.glsl");
                    }
                }

                ImGui::EndMenu();
            }
            if(ImGui::BeginMenu("2D Object"))
            {
                if(ImGui::Button("Quad"))
                {
                    createMesh = true;
                    primitive = Primitives::Quad;
                }                

                if(createMesh)
                {              
                    shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/UnlitColour_Shader.hlsl");
                    if(shader == 0)
                    {      
                        shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/UnlitColour_Shader.glsl");
                    }
                }
                ImGui::EndMenu();
            }

            if(createMesh)
            {
                                    
                EntityID ent = eManager->CreateEntity();
                eManager->AddComponent<TransformComponent>(ent);

                auto rComp = new RenderComponent();
                rComp->m_mesh = Mesh(primitive);

                rComp->m_shader = shader;

                eManager->AddComponent(ent, rComp);
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}