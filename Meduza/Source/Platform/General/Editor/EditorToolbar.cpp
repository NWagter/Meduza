#include "MePCH.h"
#include "Platform/General/Editor/EditorToolbar.h"

#include "Utils/MeduzaDebug.h"

#include "ECS/EntityManager.h"

#include "Core/Components/TransformComponent.h"
#include "Core/Components/RenderComponent.h"
#include "Core/Components/CameraComponent.h"

#include "Platform/General/ShaderLibrary.h"

#include "Core/Serialization/Serializer.h"

#include "Platform/General/Window.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#include "Platform/Windows/FileSystem/FileSystem.h"
#endif

#include "Core/Meduza.h"


Me::Editor::EditorToolbar::EditorToolbar(Me::Window& a_window)
{
    m_window = &a_window;
    m_activeCameraType = CameraType::Perspective;
    m_currentOperationType = ImGuizmo::OPERATION::TRANSLATE;
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
                eManager->CleanGame();

                #ifdef PLATFORM_WINDOWS
                std::string filePath = Files::Windows::FileSystem::SaveFile(
                    "Meduza Scene \0*.xml*\0Scene\0*.xml\0",
                     static_cast<WindowsWindow*>(m_window)->GetWindowHandle());

                size_t pos = filePath.find("Assets"); //find location of word
                filePath.erase(0,pos); //delete everything prior to location found
                std::replace(filePath.begin(), filePath.end(), '\\', '/');

                if(!filePath.empty())
                {
                    Serialization::Serializer::GetInstance()->SerializeSceneAs(filePath);
                }
                #endif
            }
            if(ImGui::MenuItem("Save"))
            {
                Meduza::ms_engineState = RUN_EDITOR; 

                #ifdef PLATFORM_WINDOWS
                    Serialization::Serializer::GetInstance()->SerializeScene();
                #endif
            }
            if(ImGui::MenuItem("Save as"))
            {
                Meduza::ms_engineState = RUN_EDITOR; 
                
                #ifdef PLATFORM_WINDOWS
                std::string filePath = Files::Windows::FileSystem::SaveFile(
                    "Meduza Scene \0*.scene*\0Scene\0*.scene\0",
                     static_cast<WindowsWindow*>(m_window)->GetWindowHandle());

                size_t pos = filePath.find("Assets"); //find location of word
                filePath.erase(0,pos); //delete everything prior to location found
                std::replace(filePath.begin(), filePath.end(), '\\', '/');

                if(!filePath.empty())
                {
                    Serialization::Serializer::GetInstance()->SerializeSceneAs(filePath);
                }
                #endif
            }
            if(ImGui::MenuItem("Load"))
            {        
                Meduza::ms_engineState = RUN_EDITOR; 

                #ifdef PLATFORM_WINDOWS
                std::string filePath = Files::Windows::FileSystem::OpenFile(
                    "Meduza Scene \0*.scene*\0Scene\0*.scene\0",
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
            if(ImGui::MenuItem("Exit"))
            {
                m_window->Quit();
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
            
            if(ImGui::BeginMenu("Prefab"))
            {
                if(ImGui::Button("Load"))
                {
                #ifdef PLATFORM_WINDOWS
                    std::string filePath = Files::Windows::FileSystem::OpenFile(
                        "Meduza Prefab \0*.prefab*\0Prefab\0*.prefab\0",
                        static_cast<WindowsWindow*>(m_window)->GetWindowHandle());

                    size_t pos = filePath.find("Assets"); //find location of word
                    filePath.erase(0,pos); //delete everything prior to location found
                    std::replace(filePath.begin(), filePath.end(), '\\', '/');
                    
                    if(!filePath.empty())
                    {
                        Serialization::Serializer::GetInstance()->DeserializeEntity(filePath);
                    }
                #endif
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

        if (ImGui::BeginMenu("Debugging"))
        {
            Debug::Settings& settings = Debug::MeduzaDebug::GetDebuggingSettings();

            ImGui::Checkbox("Collision", &settings.m_collisionDebugger);
            ImGui::Checkbox("Lines", &settings.m_lineDebugger);

            ImGui::EndMenu();
        }

        float width = ImGui::GetWindowSize().x;
        ImGui::SameLine(width * 0.5f);

        if(Meduza::GetEngineState() & RUN_EDITOR)
        {
            if(ImGui::Button(ICON_FA_PLAY))
            {            
                Serialization::Serializer::GetInstance()->SerializeScene();
                
                Meduza::ms_engineState = RUN_GAME;
            }

            if(ImGui::Button(ICON_FA_CAMERA))
            {
                EntityFilter filter;
                filter.insert(CameraComponent::s_componentID);
                filter.insert(EditorComponent::s_componentID);
                auto entities = eManager->GetEntities(filter);

                for(auto ent : entities)
                {
                    auto cameraComp = eManager->GetComponent<CameraComponent>(ent);
                    auto transformComp = eManager->GetComponent<TransformComponent>(ent);
                    
                    if(m_activeCameraType == CameraType::Perspective)
                    {
                        m_activeCameraType = cameraComp->m_cameraType = CameraType::Orthographic;                        
                    } 
                    else
                    {
                        m_activeCameraType =cameraComp->m_cameraType = CameraType::Perspective;
                    }

                    transformComp->Reset();
                    cameraComp->Reset();
                }
            }

            std::string cameraType = "Perspective";
            if(m_activeCameraType == CameraType::Orthographic)
            {
                cameraType = "Orthographic";
            }

            ImGui::Text(cameraType.c_str());

            
            if(ImGui::Button("Trans"))
            {            
                m_currentOperationType = ImGuizmo::OPERATION::TRANSLATE;
            }
            if(ImGui::Button("Rot"))
            {            
                m_currentOperationType = ImGuizmo::OPERATION::ROTATE;
            }
            if(ImGui::Button("Scale"))
            {            
                m_currentOperationType = ImGuizmo::OPERATION::SCALE;
            }
        }
        else if(Meduza::GetEngineState() & RUN_GAME)
        {        
            if(ImGui::Button(ICON_FA_PAUSE))
            {                            
                Meduza::ms_engineState = RUN_EDITOR;

                Serialization::Serializer::GetInstance()->DeserializeScene();
            }
        }      

        ImGui::EndMainMenuBar();
    }
}