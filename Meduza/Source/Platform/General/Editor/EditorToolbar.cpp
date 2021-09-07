#include "MePCH.h"
#include "Platform/General/Editor/EditorToolbar.h"

#include "ECS/EntityManager.h"

#include "Core/Components/TransformComponent.h"
#include "Core/Components/RenderComponent.h"

#include "Platform/General/ShaderLibrary.h"

#include "Core/Serialization/Serializer.h"

#include "Platform/General/Window.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#include "Platform/Windows/FileSystem/FileSystem.h"
#endif


Me::Editor::EditorToolbar::EditorToolbar(Me::Window& a_window)
{
    m_window = &a_window;
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
                #ifdef PLATFORM_WINDOWS
                std::string filePath = Files::Windows::FileSystem::SaveFile(
                    "Meduza Scene \0*.xml*\0Scene\0*.xml\0",
                     static_cast<WindowsWindow*>(m_window)->GetWindowHandle());

                size_t pos = filePath.find("Assets"); //find location of word
                filePath.erase(0,pos); //delete everything prior to location found
                std::replace(filePath.begin(), filePath.end(), '\\', '/');

                if(!filePath.empty())
                {
                    Serialization::Serializer::GetInstance()->SerializeScene(filePath);
                }
                #endif
            }
            if(ImGui::MenuItem("Load"))
            {
                #ifdef PLATFORM_WINDOWS
                std::string filePath = Files::Windows::FileSystem::OpenFile(
                    "Meduza Scene \0*.xml*\0Scene\0*.xml\0",
                     static_cast<WindowsWindow*>(m_window)->GetWindowHandle());

                size_t pos = filePath.find("Assets"); //find location of word
                filePath.erase(0,pos); //delete everything prior to location found
                std::replace(filePath.begin(), filePath.end(), '\\', '/');
                
                if(!filePath.empty())
                {
                    Serialization::Serializer::GetInstance()->DeserializeScene(filePath);
                }
                #endif
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