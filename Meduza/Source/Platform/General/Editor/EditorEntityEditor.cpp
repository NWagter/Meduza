#include "MePCH.h"

#include "Platform/General/Editor/EditorEntityEditor.h"
#include "ECS/EntityManager.h"

#include "Platform/General/Editor/EditorEntityHierarchy.h"

#include "Core/Components/TransformComponent.h"
#include "Core/Components/RenderComponent.h"
#include "Core/Components/CameraComponent.h"
#include "Core/Scripting/ScriptComponent.h"


#include "Particles/Components/ParticleSystemComponent.h"

#include "Physics/Components/PhysicsComponent.h"
#include "Physics/Components/BoxCollider2DComponent.h"
#include "Physics/Components/CircleColliderComponent.h"
#include "Physics/Components/BoxCollider3DComponent.h"
#include "Physics/Components/SphereColliderComponent.h"

#include "AI/Components/AgentComponent.h"
#include "AI/Components/NavSurfaceComponent.h"

#include "Platform/General/Resources/ShaderBase.h"
#include "Platform/General/Resources/TextureBase.h"
#include "Platform/General/Resources/MeshBase.h"
#include "Platform/General/ResourceLibrary.h"

#include "Platform/General/Events/EventSystem.h"

#include "Platform/General/Editor/EditorHelper.h"

#include "Platform/Windows/FileSystem/FileSystem.h"

Me::Editor::EntityEditor::EntityEditor(EntityHierarchy& a_entityHierarchy)
{
    m_hierarchy = &a_entityHierarchy;
    m_selectedEntity = -1;
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

void OnColliderAdded(EntityID a_ent, Me::EntityManager* a_eManager, Me::Physics::ColliderComponent* a_cComp)
{
    auto collTag = a_eManager->GetComponent<Me::Physics::ColliderTagComponent>(a_ent);
    auto debugRender = a_eManager->GetComponent<Me::DebugRenderComponent>(a_ent);
    if(collTag != nullptr)
    {
        collTag->m_collider = a_cComp;
    }
    else
    {
        Me::Physics::ColliderTagComponent* cTag = new Me::Physics::ColliderTagComponent(a_cComp);
        a_eManager->AddComponent(a_ent, cTag);
    }

    if(debugRender != nullptr)
    {
        debugRender->m_dirtyFlag = false;
    }
    else
    {                
        a_eManager->AddComponent<Me::DebugRenderComponent>(a_ent);
    }
}

static Me::Math::Vec4 s_uv = Me::Math::Vec4(0,0,0,0);

void Me::Editor::EntityEditor::Draw()
{    
	auto eManager = EntityManager::GetEntityManager();
    Me::Resources::ResourceLibrary* rLibrary = Me::Resources::ResourceLibrary::GetInstance();
	
	ImGui::Begin("Entity Editor");

    ImGui::Checkbox("Locked", &m_locked);
    
    if(!m_locked)
    {
        if(m_selectedEntity != m_hierarchy->GetSelected())
        {
            s_uv = Math::Vec4(0,0,0,0);
        }

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

        DrawComponent<RenderComponent>(eManager, "Render Component", m_selectedEntity, [&rLibrary](auto& a_comp)
        {
            ImGui::ColorEdit4("Colour", a_comp.m_colour.m_colour);

            
            std::string currentMesh = rLibrary->GetResource<Me::Resources::MeshBase>(a_comp.m_mesh)->GetFileName();
            std::string currentShader = rLibrary->GetResource<Me::Resources::ShaderBase>(a_comp.m_shader)->GetFileName();
            auto texture = rLibrary->GetResource<Me::Resources::TextureBase>(a_comp.m_texture);

            std::string currentTexture = "None";
            if(texture != nullptr)
            {
                currentTexture = Files::FileSystem::GetFileName(texture->GetPath());
            }
            

            std::string newModelPath = "";
            Mesh primitive = 999999;

            if (ImGui::BeginCombo("Model", currentMesh.c_str())) // The second parameter is the label previewed before opening the combo.
            {
                Files::BrowseData data = Files::BrowseData();
                Files::Windows::FileSystem::GetFilesOfType(data, Files::FileType::Model);
                

                bool is_selected = false;

                for(auto file : data.m_files)
                {
                    if (ImGui::Selectable(file->m_name.c_str(), &is_selected))
                    {
                        newModelPath = file->m_path;
                    }
                }
                
                if (ImGui::Selectable("Cube", &is_selected))
                {
                    primitive = (Mesh)Primitives::Cube;
                }
                if (ImGui::Selectable("Sphere", &is_selected))
                {
                    primitive = (Mesh)Primitives::Sphere;
                }
                if (ImGui::Selectable("Plane", &is_selected))
                {
                    primitive = (Mesh)Primitives::Plane;
                }
                if (ImGui::Selectable("Quad", &is_selected))
                {
                    primitive = (Mesh)Primitives::Quad;
                }

                ImGui::EndCombo();
            }
            if(!newModelPath.empty())
            {
                a_comp.m_mesh = rLibrary->LoadResource<Resources::MeshBase>(newModelPath)->GetID();
            }else if(primitive < 10)
            {
                a_comp.m_mesh = primitive;
            }
        
            std::string newShaderPath = "";

            if (ImGui::BeginCombo("Shader", currentShader.c_str())) // The second parameter is the label previewed before opening the combo.
            {
                Files::BrowseData data = Files::BrowseData();
                Files::Windows::FileSystem::GetFilesOfType(data, Files::FileType::Shader);

                bool is_selected = false;

                for(auto file : data.m_files)
                {
                    if (ImGui::Selectable(file->m_name.c_str(), &is_selected))
                    {
                        newShaderPath = file->m_path;
                    }
                }

                ImGui::EndCombo();
            }
            if(!newShaderPath.empty())
            {
                a_comp.m_shader = rLibrary->LoadResource<Resources::ShaderBase>(newShaderPath)->GetID();
            }
            
            std::string newTexturePath = "";

            if (ImGui::BeginCombo("Texture", currentTexture.c_str())) // The second parameter is the label previewed before opening the combo.
            {
                Files::BrowseData data = Files::BrowseData();
                Files::Windows::FileSystem::GetFilesOfType(data, Files::FileType::Texture);

                bool is_selected = false;

                for(auto file : data.m_files)
                {
                    if (ImGui::Selectable(file->m_name.c_str(), &is_selected))
                    {
                        newTexturePath = file->m_path;
                    }
                }

                ImGui::EndCombo();
            }
            if(!newTexturePath.empty())
            {
                a_comp.m_texture = rLibrary->LoadResource<Resources::TextureBase>(newTexturePath)->GetID();
            }

            if(a_comp.m_texture > 0)
            {           
                if(s_uv == Math::Vec4(0,0,0,0))
                {
                    Math::Vec2 size = rLibrary->GetResource<Resources::TextureBase>(a_comp.m_texture)->GetSize();
                    Math::Vec4 tC = a_comp.m_textureCoords;
                    float y = 0;
                    if(tC.m_y != 0)
                    {
                        y = (tC.m_y * size.m_y) - 0.5f;
                    }
                    float w = size.m_y;
                    if(tC.m_w != 1)
                    {
                        w = (tC.m_w * size.m_y) + 0.5f;
                    }


                    s_uv = Math::Vec4(tC.m_x * size.m_x, y, tC.m_z * size.m_x, w);
                }

                Helper::EditorHelper::DrawVec4Prop("TextureRect", s_uv);

                if(ImGui::Button("Apply TextureRect"))
                {
                    Math::Vec2 size = rLibrary->GetResource<Resources::TextureBase>(a_comp.m_texture)->GetSize();
                    a_comp.m_textureCoords = Animation::GetUV(s_uv, size);
                }
            }

        
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
            ImGui::DragInt("Camera Layer", &a_comp.m_cameralayer);
        });

        DrawComponent<Particle::ParticleSystemComponent>(eManager, "ParticleSystem Component", m_selectedEntity, [](auto& a_comp)
        {
                ImGui::DragFloat("spawnRate", &a_comp.m_spawnRate);
                ImGui::DragInt("maxParticles", &a_comp.m_maxParticles);

                ImGui::DragFloat("Lifetime", &a_comp.m_particle.m_initialLifeTime);
                ImGui::DragFloat("Speed", &a_comp.m_particle.m_speed);
                ImGui::ColorEdit4("Colour", a_comp.m_particle.m_initalColour.m_colour);
                Helper::EditorHelper::DrawVec3Prop("Direction", a_comp.m_particle.m_direction);
                ImGui::Checkbox("RandomRange", &a_comp.m_particle.m_randomDirection);
                if (a_comp.m_particle.m_randomDirection)
                {
                    Helper::EditorHelper::DrawVec3Prop("DirectionRange", a_comp.m_particle.m_directionRange);
                }
        });

        DrawComponent<Physics::PhysicsComponent>(eManager, "Physics Component", m_selectedEntity, [](auto& a_comp)
        {
            ImGui::Checkbox("Gravity", &a_comp.m_gravity);      
            ImGui::DragFloat("BodyMass", &a_comp.m_bodyMass);
            ImGui::DragFloat("Drag", &a_comp.m_drag);
            ImGui::DragFloat("Friction", &a_comp.m_friction);

            ImGui::Checkbox("Debug Hit Normals", &a_comp.m_debugHitNormals);
        });

        DrawComponent<Physics::BoxCollider2DComponent>(eManager, "Box2DCollider Component", m_selectedEntity, [](auto& a_comp)
        {
            Helper::EditorHelper::DrawVec2Prop("ColliderScale", a_comp.m_colliderSize);
            Helper::EditorHelper::DrawVec2Prop("ColliderOffset", a_comp.m_colliderOffset);

            const char* collisionTypes[] = { "Overlap", "Block"};
            const char* currentCollisionType = collisionTypes[int(a_comp.m_collisionType)];

            if(ImGui::BeginCombo("CollisionType", currentCollisionType))
            {
                for(int i = 0; i < 2;i++)
                {
                    bool isSelected = currentCollisionType == collisionTypes[i];

                    if(ImGui::Selectable(collisionTypes[i], isSelected))
                    {
                        currentCollisionType = collisionTypes[i];
                        a_comp.m_collisionType = Physics::CollisionType(i);
                    }

                    if(isSelected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                
                
                ImGui::EndCombo();
            }
        });     
        DrawComponent<Physics::CircleColliderComponent>(eManager, "CircleCollider Component", m_selectedEntity, [](auto& a_comp)
            {
                ImGui::DragFloat("Radius", &a_comp.m_radius);
                Helper::EditorHelper::DrawVec2Prop("ColliderOffset", a_comp.m_colliderOffset);

                const char* collisionTypes[] = { "Overlap", "Block" };
                const char* currentCollisionType = collisionTypes[int(a_comp.m_collisionType)];

                if (ImGui::BeginCombo("CollisionType", currentCollisionType))
                {
                    for (int i = 0; i < 2; i++)
                    {
                        bool isSelected = currentCollisionType == collisionTypes[i];

                        if (ImGui::Selectable(collisionTypes[i], isSelected))
                        {
                            currentCollisionType = collisionTypes[i];
                            a_comp.m_collisionType = Physics::CollisionType(i);
                        }

                        if (isSelected)
                        {
                            ImGui::SetItemDefaultFocus();
                        }
                    }


                    ImGui::EndCombo();
                }
            });
        DrawComponent<Physics::BoxCollider3DComponent>(eManager, "Box3DCollider Component", m_selectedEntity, [](auto& a_comp)
        {
            Helper::EditorHelper::DrawVec3Prop("ColliderScale", a_comp.m_colliderSize);
            Helper::EditorHelper::DrawVec3Prop("ColliderOffset", a_comp.m_colliderOffset);

            const char* collisionTypes[] = { "Overlap", "Block"};
            const char* currentCollisionType = collisionTypes[int(a_comp.m_collisionType)];

            if(ImGui::BeginCombo("CollisionType", currentCollisionType))
            {
                for(int i = 0; i < 2;i++)
                {
                    bool isSelected = currentCollisionType == collisionTypes[i];

                    if(ImGui::Selectable(collisionTypes[i], isSelected))
                    {
                        currentCollisionType = collisionTypes[i];
                        a_comp.m_collisionType = Physics::CollisionType(i);
                    }

                    if(isSelected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                
                
                ImGui::EndCombo();
            }
        });
        DrawComponent<Physics::SphereColliderComponent>(eManager, "SphereCollider Component", m_selectedEntity, [](auto& a_comp)
        {
            ImGui::DragFloat("Radius", &a_comp.m_radius);
            Helper::EditorHelper::DrawVec3Prop("ColliderOffset", a_comp.m_colliderOffset);

            const char* collisionTypes[] = { "Overlap", "Block"};
            const char* currentCollisionType = collisionTypes[int(a_comp.m_collisionType)];

            if(ImGui::BeginCombo("CollisionType", currentCollisionType))
            {
                for(int i = 0; i < 2;i++)
                {
                    bool isSelected = currentCollisionType == collisionTypes[i];

                    if(ImGui::Selectable(collisionTypes[i], isSelected))
                    {
                        currentCollisionType = collisionTypes[i];
                        a_comp.m_collisionType = Physics::CollisionType(i);
                    }

                    if(isSelected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                
                
                ImGui::EndCombo();
            }
        }); 
        
        DrawComponent<Scripting::ScriptComponent>(eManager, "Script Component", m_selectedEntity, [](auto& a_comp)
        {
            size_t size = a_comp.m_scripts.size();
            std::vector<size_t> itemsToRemove;
            for(size_t i = 0; i < size; i++)
            {
                std::string fileName = Files::FileSystem::GetFileName(a_comp.m_scripts[i]);
                ImGui::PushID(fileName.c_str());

                std::string newScriptPath = a_comp.m_scripts[i];
                if (ImGui::BeginCombo(("##" + fileName).c_str(), fileName.c_str())) // The second parameter is the label previewed before opening the combo.
                {
                    bool is_selected;
                    Files::BrowseData data = Files::BrowseData();
                    Files::Windows::FileSystem::GetFilesOfType(data, Files::FileType::Script);

                    for(auto file : data.m_files)
                    {
                        if (ImGui::Selectable(file->m_name.c_str(), &is_selected))
                        {
                            newScriptPath = file->m_path;
                        }
                    }

                    ImGui::EndCombo();
                }

                if(newScriptPath != a_comp.m_scripts[i])
                {
                    a_comp.m_scripts[i] = newScriptPath;
                }
                
                ImGui::SameLine();
                if(ImGui::Button("X"))
                {
                    itemsToRemove.push_back(i);
                }
                ImGui::PopID();
            }

            if(ImGui::Button("Add New Script"))
            {
                a_comp.AddScript();
            }

            for(auto i : itemsToRemove)
            {
                a_comp.RemoveScript(i);
            }
        });

        DrawComponent<AI::AgentComponent>(eManager, "Agent Component", m_selectedEntity, [](auto& a_comp)
        {
            Helper::EditorHelper::DrawVec3Prop("TargetPosition", a_comp.m_targetLocation);

            ImGui::DragFloat("AgentSpeed", &a_comp.m_agentSpeed);
            ImGui::DragFloat("AgentStopdistance", &a_comp.m_stopDistance);
        });
        DrawComponent<AI::NavSurfaceComponent>(eManager, "NavSurface Component", m_selectedEntity, [](auto& a_comp)
        {
            Math::Vec2 gS = a_comp.m_gridSize;
            Math::Vec2 cS = a_comp.m_cellSize;

            Helper::EditorHelper::DrawVec2Prop("GridSize", a_comp.m_gridSize);
            Helper::EditorHelper::DrawVec2Prop("CellSize", a_comp.m_cellSize);
            
            if(ImGui::Button("Print Grid"))
            {
                a_comp.m_printGrid = true;
            }

            if(gS != a_comp.m_gridSize || cS != a_comp.m_cellSize)
            {
                a_comp.OnChange();
            }
        });
    }

    if(eManager->EntityExists(m_selectedEntity) && ImGui::Button("Add Component"))
    {
        ImGui::OpenPopup("AddComponent");
    }

    if(ImGui::BeginPopup("AddComponent"))
    {
        if(ImGui::MenuItem("RenderComponent"))
        {
            auto rComp = new RenderComponent();
            rComp->m_mesh = Mesh(Primitives::Quad);

            Me::Shader shader = rLibrary->LoadResource<Resources::ShaderBase>("Assets/Shaders/LitColour_Shader.hlsl")->GetID();
            if(shader == 0)
            {      
                shader = rLibrary->LoadResource<Resources::ShaderBase>("Assets/Shaders/LitColour_Shader.glsl")->GetID();
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
        if(ImGui::MenuItem("Physics Component"))
        {
            auto pComp = new Physics::PhysicsComponent();
            eManager->AddComponent(m_selectedEntity, pComp);
            ImGui::CloseCurrentPopup();
        }
        if(ImGui::MenuItem("Box2D Component"))
        {
            auto cComp = new Physics::BoxCollider2DComponent();
            eManager->AddComponent(m_selectedEntity, cComp);
            eManager->AddComponent<DebugRenderComponent>(m_selectedEntity);

            OnColliderAdded(m_selectedEntity, eManager, cComp);

            ImGui::CloseCurrentPopup();
        }        
        if (ImGui::MenuItem("Circle Component"))
        {
            auto cComp = new Physics::CircleColliderComponent();
            eManager->AddComponent(m_selectedEntity, cComp);
            eManager->AddComponent<DebugRenderComponent>(m_selectedEntity);

            OnColliderAdded(m_selectedEntity, eManager, cComp);

            ImGui::CloseCurrentPopup();
        }
        if(ImGui::MenuItem("Box3D Component"))
        {
            auto cComp = new Physics::BoxCollider3DComponent();
            eManager->AddComponent(m_selectedEntity, cComp);

            OnColliderAdded(m_selectedEntity, eManager, cComp);

            ImGui::CloseCurrentPopup();
        }
        if(ImGui::MenuItem("Sphere Component"))
        {
            auto cComp = new Physics::SphereColliderComponent();
            eManager->AddComponent(m_selectedEntity, cComp);
            eManager->AddComponent<DebugRenderComponent>(m_selectedEntity);

            OnColliderAdded(m_selectedEntity, eManager, cComp);

            ImGui::CloseCurrentPopup();
        }
        if(ImGui::MenuItem("Script Component"))
        {
            auto sC = eManager->GetComponent<Scripting::ScriptComponent>(m_selectedEntity);
            if(sC == nullptr)
            {
                auto pComp = new Scripting::ScriptComponent();
                pComp->AddScript();
                eManager->AddComponent(m_selectedEntity, pComp);
            }
            else
            {
                sC->AddScript();
            }

            ImGui::CloseCurrentPopup();
        }
        if (ImGui::MenuItem("ParticleSystem Component"))
        {
            auto pComp = new Particle::ParticleSystemComponent();
            eManager->AddComponent(m_selectedEntity, pComp);
            ImGui::CloseCurrentPopup();
        }
        if(ImGui::MenuItem("Agent Component"))
        {
            auto aComp = new AI::AgentComponent();
            eManager->AddComponent(m_selectedEntity, aComp);
            ImGui::CloseCurrentPopup();
        }
        if(ImGui::MenuItem("Nav Surface Component"))
        {
            auto nSComp = new AI::NavSurfaceComponent();
            eManager->AddComponent(m_selectedEntity, nSComp);
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

	ImGui::End();
}