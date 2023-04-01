#include "MePCH.h"
#include "Platform/General/Editor/EditorToolbar.h"

#include "Utils/MeduzaDebug.h"

#include "ECS/EntityManager.h"

#include "Core/Components/TransformComponent.h"
#include "Core/Components/RenderComponent.h"
#include "Core/Components/CameraComponent.h"

#include "Core/Serialization/Serializer.h"

#include "Platform/General/Editor/EditorProjectManager.h"
#include "Platform/General/Window.h"
#include "Platform/General/ResourceLibrary.h"
#include "Platform/General/Resources/ShaderBase.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#include "Platform/Windows/FileSystem/FileSystem.h"
#endif

#include "Core/Meduza.h"


Me::Editor::EditorToolbar::EditorToolbar(Me::Window& a_window, EditorProjectManager& a_projectManager)
{
    m_window = &a_window;
    m_projectManager = &a_projectManager;
    m_currentOperationType = ImGuizmo::OPERATION::TRANSLATE;


    auto eManager = EntityManager::GetEntityManager();
    EntityFilter filter;
    filter.insert(CameraComponent::s_componentID);
    filter.insert(EditorComponent::s_componentID);
    auto entities = eManager->GetEntities(filter);

    for (auto ent : entities)
    {
        auto const& cameraComp = eManager->GetComponent<CameraComponent>(ent);

        m_activeCameraType = cameraComp->m_cameraType;
    }
}

Me::Editor::EditorToolbar::~EditorToolbar()
{
    
}

void Me::Editor::EditorToolbar::Draw()
{
    EntityManager* eManager = EntityManager::GetEntityManager();

    if(ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Project"))
        {
            if (ImGui::Button("New Project"))
            {
                Meduza::ms_engineState = RUN_EDITOR;
                m_projectManager->SetEditorState(ProjectManagerState::CreateNew, true);
            }
            if (ImGui::Button("Load Project"))
            {
                Meduza::ms_engineState = RUN_EDITOR;
                m_projectManager->SetEditorState(ProjectManagerState::LoadProject, true);
            }

            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("New Scene"))
            {
                Meduza::ms_engineState = RUN_EDITOR;
                eManager->CleanGame();

                #ifdef PLATFORM_WINDOWS
                std::string filePath = Files::Windows::FileSystem::SaveFile(
                    "Meduza Scene \0*.xml*\0Scene\0*.xml\0",
                     static_cast<WindowsWindow*>(m_window)->GetWindowHandle());

                size_t pos = filePath.find("Projects"); //find location of word
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
                #ifdef PLATFORM_WINDOWS
                    Serialization::Serializer::GetInstance()->SerializeScene();
                #endif
            }
            if(ImGui::MenuItem("Save as"))
            {
                #ifdef PLATFORM_WINDOWS
                std::string filePath = Files::Windows::FileSystem::SaveFile(
                    "Meduza Scene \0*.scene*\0Scene\0*.scene\0",
                     static_cast<WindowsWindow*>(m_window)->GetWindowHandle());

                size_t pos = filePath.find("Projects"); //find location of word
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

                size_t pos = filePath.find("Projects"); //find location of word
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
        std::string primitiveName = "Cube";
        Shader shader = 0;

        if(ImGui::BeginMenu("Create"))
        {
            if(ImGui::BeginMenu("3D Object"))
            {
                if(ImGui::Button("Cube"))
                {
                    createMesh = true;
                    primitive = Primitives::Cube;
                    primitiveName = "Cube";
                }
                if(ImGui::Button("Sphere"))
                {
                    createMesh = true;
                    primitive = Primitives::Sphere;
                    primitiveName = "Sphere";
                }
                if(ImGui::Button("Plane"))
                {
                    createMesh = true;
                    primitive = Primitives::Plane; 
                    primitiveName = "Plane";
                }
                if(ImGui::Button("Quad"))
                {
                    createMesh = true;
                    primitive = Primitives::Quad;
                    primitiveName = "Quad";
                }

                if(createMesh)
                {              
                    shader = Me::Resources::ResourceLibrary::GetInstance()->LoadResource<Resources::ShaderBase>("Assets/Shaders/LitColour_Shader.glsl")->GetID();
                }

                ImGui::EndMenu();
            }
            if(ImGui::BeginMenu("2D Object"))
            {
                if(ImGui::Button("Quad"))
                {
                    createMesh = true;
                    primitive = Primitives::Quad;
                    primitiveName = "Quad";
                }                

                if(createMesh)
                {
                    shader = Me::Resources::ResourceLibrary::GetInstance()->LoadResource<Resources::ShaderBase>("Assets/Shaders/UnlitColour_Shader.glsl")->GetID();
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
                                    
                EntityID ent = eManager->CreateEntity(primitiveName);
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

            ImGui::Text("Time");
            ImGui::DragFloat("TimeScale", &settings.m_timeScale, 0.1f, 0, 5.0f);

            ImGui::Text("Physics Debugging");
            ImGui::Checkbox("GJK", &settings.m_gjkDebugger);
            ImGui::Checkbox("RayIntersections", &settings.m_rayIntersections);
            ImGui::Checkbox("Collision", &settings.m_collisionDebugger);
            ImGui::Separator();
            ImGui::Checkbox("Lines", &settings.m_lineDebugger);
            ImGui::DragFloat("Line Lenght", &settings.m_debugLineLenght, 0.1f, 0, 5.0f);
            ImGui::Checkbox("HitPoints", &settings.m_drawHitPoints);
            ImGui::Separator();
            ImGui::Checkbox("Circles", &settings.m_debugCircle);
            ImGui::Separator();
            ImGui::Checkbox("Show Vertices", &settings.m_showVertices);
            ImGui::DragFloat("Vertices Size", &settings.m_scaleVertices, 0.1f, 0, 5.0f);

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

                    if (cameraComp->m_cameraType != m_activeCameraType)
                    {
                        m_activeCameraType = cameraComp->m_cameraType;
                    }

                    cameraComp->Reset();
                    transformComp->Reset();
                    
                    if(m_activeCameraType == CameraType::Perspective)
                    {
                        m_activeCameraType = cameraComp->m_cameraType = CameraType::Orthographic;                        
                    } 
                    else
                    {
                        m_activeCameraType = cameraComp->m_cameraType = CameraType::Perspective;
                        transformComp->m_translation.m_z = -10;
                    }
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
            if (ImGui::Button("Rotation"))
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
                Meduza::ms_engineState = RUN_PAUSED;
            }
            if (ImGui::Button(ICON_FA_STOP))
            {
                Meduza::ms_engineState = RUN_EDITOR;

                Serialization::Serializer::GetInstance()->DeserializeScene();
            }
        }
        else if (Meduza::GetEngineState() & RUN_PAUSED)
        {
            if (ImGui::Button(ICON_FA_PLAY))
            {
                Meduza::ms_engineState = RUN_GAME;
            }
            if (ImGui::Button(ICON_FA_STOP))
            {
                Meduza::ms_engineState = RUN_EDITOR;

                Serialization::Serializer::GetInstance()->DeserializeScene();
            }
        }

        ImGui::Checkbox("Stats", &Debug::MeduzaDebug::GetDebuggingSettings().m_showStats);

        ImGui::EndMainMenuBar();
    }
}