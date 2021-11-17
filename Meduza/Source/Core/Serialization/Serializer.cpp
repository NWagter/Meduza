#include "MePCH.h"
#include "Core/Serialization/Serializer.h"

#include "ECS/EntityManager.h"

#include "Core/Components/TransformComponent.h"
#include "Core/Components/RenderComponent.h"
#include "Core/Components/CameraComponent.h"

#include "Core/Scripting/ScriptComponent.h"

#include "Physics/Components/PhysicsComponent.h"
#include "Physics/Components/BoxCollider2DComponent.h"
#include "Physics/Components/CircleColliderComponent.h"
#include "Physics/Components/BoxCollider3DComponent.h"
#include "Physics/Components/SphereColliderComponent.h"

#include "AI/Components/AgentComponent.h"

#include "Platform/General/ShaderLibrary.h"
#include "Platform/General/Resources/ShaderBase.h"
#include "Platform/General/TextureLibrary.h"
#include "Platform/General/Resources/TextureBase.h"
#include "Platform/General/MeshLibrary.h"
#include "Platform/General/Resources/MeshBase.h"

#include "Platform/General/FileSystem/FileSystem.h"

Me::Serialization::Serializer* Me::Serialization::Serializer::ms_instance = nullptr;

Me::Serialization::Serializer::Serializer(std::string a_file)
{
    if(ms_instance != nullptr)
    {
        ME_CORE_ASSERT_M(false, "Can only have one instance of Serializer!")
    }

    ms_instance = this;
}

void Me::Serialization::Serializer::DestroySerializer()
{
    delete ms_instance;
    ms_instance = nullptr;
}

Me::Serialization::Serializer::~Serializer()
{

}

template<typename T, typename FUNCTION>
static void CanSerialize(Me::EntityManager* a_eManager, EntityID a_entity, cereal::XMLOutputArchive& a_archive , FUNCTION a_function)
{
    auto component = a_eManager->GetComponent<T>(a_entity);

    if(component != nullptr)
    {
        std::string compId = std::to_string(T::s_componentID);
        a_archive.setNextName(compId.c_str());
        a_archive.startNode(); 
        a_function(component);
        a_archive.finishNode();
    }
}

template<typename T, typename FUNCTION>
static bool CanDeserialize(cereal::XMLInputArchive& a_archive , FUNCTION a_function)
{
    if(a_archive.getNodeName() == nullptr)
    {
        return false;
    }

    if(std::to_string(T::s_componentID) == a_archive.getNodeName())
    {
        auto comp = new T();
        
        a_archive.startNode(); 
        a_function(comp);
        a_archive.finishNode();

        return true;
    }

    return false;
}

bool SerializeSceneA(std::string a_path)
{
    std::ofstream os(a_path.c_str());
    cereal::XMLOutputArchive archive(os);

    Me::EntityManager* eManager = Me::EntityManager::GetEntityManager();
    archive.setNextName("SceneData"); 
    archive.startNode();  

    archive(cereal::make_nvp("EntityAmount" , eManager->GetGameEntityAmount()));
    archive.finishNode();

    for (auto ent : eManager->GetEntities())
    {     
        if(eManager->GetComponent<Me::EditorComponent>(ent.first) != nullptr)
        {
            continue;
        }

        archive.startNode();    
        archive.setNextName("Components"); 
        archive(cereal::make_nvp("ComponentAmount" , (int)ent.second.size()));

        archive.startNode(); 
        CanSerialize<Me::TagComponent>(eManager, ent.first, archive, [&archive](auto& a_comp)
        {  
            archive(cereal::make_nvp("Tag", a_comp->m_tag));
        });        
        
        CanSerialize<Me::TransformComponent>(eManager, ent.first, archive, [&archive](auto& a_comp)
        {          
            archive(cereal::make_nvp("Translation", a_comp->m_translation.m_xyz));
            archive(cereal::make_nvp("Rotation", a_comp->m_rotation.m_xyz));
            archive(cereal::make_nvp("Scale", a_comp->m_scale.m_xyz));
            
        });   

        CanSerialize<Me::RenderComponent>(eManager, ent.first, archive, [&archive](auto& a_comp)
        {          
            archive(cereal::make_nvp("Colour", a_comp->m_colour.m_colour));   

            if(a_comp->m_mesh > 10)
            {
                auto mesh = Me::Resources::MeshLibrary::GetMesh(a_comp->m_mesh);  
                archive(cereal::make_nvp("Mesh", mesh->GetPath()));   
            }   
            else
            {
                archive(cereal::make_nvp("Mesh", a_comp->m_mesh)); 
            }

            auto shader = Me::Resources::ShaderLibrary::GetShader(a_comp->m_shader);
            archive(cereal::make_nvp("Shader", shader->GetPath()));    
            auto texture = Me::Resources::TextureLibrary::GetTexture(a_comp->m_texture);
            if(texture != nullptr)
            {
                archive(cereal::make_nvp("Texture", texture->GetPath())); 
            } 
            else            
            {
                archive(cereal::make_nvp("Texture", ""));  
            }
            archive(cereal::make_nvp("UV", a_comp->m_textureCoords.m_xyzw));
        });   

        CanSerialize<Me::CameraComponent>(eManager, ent.first, archive, [&archive](auto& a_comp)
        {          
            archive(cereal::make_nvp("Far", a_comp->m_far)); 
            archive(cereal::make_nvp("Near", a_comp->m_near)); 
            archive(cereal::make_nvp("Size", a_comp->m_size.m_xy)); 
            archive(cereal::make_nvp("OrthoScale", a_comp->m_orthoScale)); 
            archive(cereal::make_nvp("CameraLayer", a_comp->m_cameralayer)); 
            archive(cereal::make_nvp("CameraType", (int)a_comp->m_cameraType));     
                  
        }); 
        
        CanSerialize<Me::Physics::PhysicsComponent>(eManager, ent.first, archive, [&archive](auto& a_comp)
        {          
            archive(cereal::make_nvp("Gravity", a_comp->m_gravity));  
            archive(cereal::make_nvp("Body_Mass", a_comp->m_bodyMass));    
            archive(cereal::make_nvp("Body_Drag", a_comp->m_drag));
            archive(cereal::make_nvp("Body_Friction", a_comp->m_friction));
            archive(cereal::make_nvp("DrawCollisionLines", a_comp->m_debugHitNormals));
        }); 

        CanSerialize<Me::Physics::BoxCollider2DComponent>(eManager, ent.first, archive, [&archive](auto& a_comp)
        {          
            archive(cereal::make_nvp("CollisionType", (int)a_comp->m_collisionType)); 
            archive(cereal::make_nvp("CollisionLayer", (int)a_comp->m_collisionLayer));    
            archive(cereal::make_nvp("CollisionScale", a_comp->m_colliderSize.m_xy)); 
            archive(cereal::make_nvp("CollisionOffset", a_comp->m_colliderOffset.m_xy));   
        }); 
        CanSerialize<Me::Physics::CircleColliderComponent>(eManager, ent.first, archive, [&archive](auto& a_comp)
        {
            archive(cereal::make_nvp("CollisionType", (int)a_comp->m_collisionType));
            archive(cereal::make_nvp("CollisionLayer", (int)a_comp->m_collisionLayer));
            archive(cereal::make_nvp("CollisionScale", a_comp->m_radius));
            archive(cereal::make_nvp("CollisionOffset", a_comp->m_colliderOffset.m_xy));
        });
        CanSerialize<Me::Physics::BoxCollider3DComponent>(eManager, ent.first, archive, [&archive](auto& a_comp)
        {          
            archive(cereal::make_nvp("CollisionType", (int)a_comp->m_collisionType)); 
            archive(cereal::make_nvp("CollisionLayer", (int)a_comp->m_collisionLayer));  
            archive(cereal::make_nvp("CollisionScale", a_comp->m_colliderSize.m_xyz)); 
            archive(cereal::make_nvp("CollisionOffset", a_comp->m_colliderOffset.m_xyz)); 
        }); 
        CanSerialize<Me::Physics::SphereColliderComponent>(eManager, ent.first, archive, [&archive](auto& a_comp)
        {          
            archive(cereal::make_nvp("CollisionType", (int)a_comp->m_collisionType)); 
            archive(cereal::make_nvp("CollisionLayer", (int)a_comp->m_collisionLayer));  
            archive(cereal::make_nvp("CollisionScale", a_comp->m_radius)); 
            archive(cereal::make_nvp("CollisionOffset", a_comp->m_colliderOffset.m_xyz)); 
        }); 

        CanSerialize<Me::Scripting::ScriptComponent>(eManager, ent.first, archive, [&archive](auto& a_comp)
        {                      
            archive(cereal::make_nvp("ScriptAmount", (int)a_comp->m_scripts.size()));  

            for(size_t i = 0; i < a_comp->m_scripts.size();i++)
            {
                std::string scriptPath = "ScriptPath" + std::to_string(i);
                archive(cereal::make_nvp(scriptPath.c_str(), a_comp->m_scripts[i]));  
            }          
        }); 

        CanSerialize<Me::AI::AgentComponent>(eManager, ent.first, archive, [&archive](auto& a_comp)
        {                 
            archive(cereal::make_nvp("TargetLocation", a_comp->m_targetLocation.m_xyz)); 
            archive(cereal::make_nvp("AgentSpeed", a_comp->m_agentSpeed));
            archive(cereal::make_nvp("AgentStopDistance", a_comp->m_stopDistance));        
        });   

        archive.finishNode();        
        archive.finishNode();
    }
    
    return true;
}

bool SerializeEntityA(std::string a_path, EntityID a_entity)
{
    std::ofstream os(a_path.c_str());
    cereal::XMLOutputArchive archive(os);

    Me::EntityManager* eManager = Me::EntityManager::GetEntityManager();
    archive.setNextName("PrefabData"); 
    archive.startNode();  

    EntityFilter filter = eManager->GetEntities().at(a_entity);
   
    archive.setNextName("Entity"); 
    archive.startNode();    
    archive(cereal::make_nvp("EntityName", eManager->GetComponent<Me::TagComponent>(a_entity)->m_tag));
    archive.setNextName("Components"); 
    archive(cereal::make_nvp("ComponentAmount" , (int)filter.size()));

    archive.startNode(); 
    CanSerialize<Me::TagComponent>(eManager, a_entity, archive, [&archive](auto& a_comp)
    {  
        archive(cereal::make_nvp("Tag", a_comp->m_tag));
    });        
    
    CanSerialize<Me::TransformComponent>(eManager, a_entity, archive, [&archive](auto& a_comp)
    {          
        archive(cereal::make_nvp("Translation", a_comp->m_translation.m_xyz));
        archive(cereal::make_nvp("Rotation", a_comp->m_rotation.m_xyz));
        archive(cereal::make_nvp("Scale", a_comp->m_scale.m_xyz));
        
    });   

    CanSerialize<Me::RenderComponent>(eManager, a_entity, archive, [&archive](auto& a_comp)
    {          
        archive(cereal::make_nvp("Colour", a_comp->m_colour.m_colour));   

        if(a_comp->m_mesh > 10)
        {
            auto mesh = Me::Resources::MeshLibrary::GetMesh(a_comp->m_mesh);  
            archive(cereal::make_nvp("Mesh", mesh->GetPath()));   
        }   
        else
        {
            archive(cereal::make_nvp("Mesh", a_comp->m_mesh)); 
        }

        auto shader = Me::Resources::ShaderLibrary::GetShader(a_comp->m_shader);
        archive(cereal::make_nvp("Shader", shader->GetPath()));    
        auto texture = Me::Resources::TextureLibrary::GetTexture(a_comp->m_texture);
        if(texture != nullptr)
        {
            archive(cereal::make_nvp("Texture", texture->GetPath())); 
        } 
        else            
        {
            archive(cereal::make_nvp("Texture", ""));  
        }
        archive(cereal::make_nvp("UV", a_comp->m_textureCoords.m_xyzw));
    });   

    CanSerialize<Me::CameraComponent>(eManager, a_entity, archive, [&archive](auto& a_comp)
    {          
        archive(cereal::make_nvp("Far", a_comp->m_far)); 
        archive(cereal::make_nvp("Near", a_comp->m_near)); 
        archive(cereal::make_nvp("Size", a_comp->m_size.m_xy)); 
        archive(cereal::make_nvp("OrthoScale", a_comp->m_orthoScale)); 
        archive(cereal::make_nvp("CameraLayer", a_comp->m_cameralayer)); 
        archive(cereal::make_nvp("CameraType", (int)a_comp->m_cameraType));     
                
    }); 
    
    CanSerialize<Me::Physics::PhysicsComponent>(eManager, a_entity, archive, [&archive](auto& a_comp)
    {          
        archive(cereal::make_nvp("Gravity", a_comp->m_gravity));      
        archive(cereal::make_nvp("Body_Mass", a_comp->m_bodyMass)); 
        archive(cereal::make_nvp("Body_Drag", a_comp->m_drag));
        archive(cereal::make_nvp("Body_Friction", a_comp->m_friction));
        archive(cereal::make_nvp("DrawCollisionLines", a_comp->m_debugHitNormals));
    }); 

    CanSerialize<Me::Physics::BoxCollider2DComponent>(eManager, a_entity, archive, [&archive](auto& a_comp)
    {          
        archive(cereal::make_nvp("CollisionType", (int)a_comp->m_collisionType)); 
        archive(cereal::make_nvp("CollisionLayer", (int)a_comp->m_collisionLayer));    
        archive(cereal::make_nvp("CollisionScale", a_comp->m_colliderSize.m_xy)); 
        archive(cereal::make_nvp("CollisionOffset", a_comp->m_colliderOffset.m_xy));   
    }); 
    CanSerialize<Me::Physics::CircleColliderComponent>(eManager, a_entity, archive, [&archive](auto& a_comp)
    {
        archive(cereal::make_nvp("CollisionType", (int)a_comp->m_collisionType));
        archive(cereal::make_nvp("CollisionLayer", (int)a_comp->m_collisionLayer));
        archive(cereal::make_nvp("CollisionScale", a_comp->m_radius));
        archive(cereal::make_nvp("CollisionOffset", a_comp->m_colliderOffset.m_xy));
    });
    CanSerialize<Me::Physics::BoxCollider3DComponent>(eManager, a_entity, archive, [&archive](auto& a_comp)
    {          
        archive(cereal::make_nvp("CollisionType", (int)a_comp->m_collisionType)); 
        archive(cereal::make_nvp("CollisionLayer", (int)a_comp->m_collisionLayer));  
        archive(cereal::make_nvp("CollisionScale", a_comp->m_colliderSize.m_xyz)); 
        archive(cereal::make_nvp("CollisionOffset", a_comp->m_colliderOffset.m_xyz)); 
    }); 
    CanSerialize<Me::Physics::SphereColliderComponent>(eManager, a_entity, archive, [&archive](auto& a_comp)
    {          
        archive(cereal::make_nvp("CollisionType", (int)a_comp->m_collisionType)); 
        archive(cereal::make_nvp("CollisionLayer", (int)a_comp->m_collisionLayer));  
        archive(cereal::make_nvp("CollisionScale", a_comp->m_radius)); 
        archive(cereal::make_nvp("CollisionOffset", a_comp->m_colliderOffset.m_xyz)); 
    }); 

    CanSerialize<Me::Scripting::ScriptComponent>(eManager, a_entity, archive, [&archive](auto& a_comp)
    {                      
        archive(cereal::make_nvp("ScriptAmount", (int)a_comp->m_scripts.size()));  

        for(size_t i = 0; i < a_comp->m_scripts.size();i++)
        {
            std::string scriptPath = "ScriptPath" + std::to_string(i);
            archive(cereal::make_nvp(scriptPath.c_str(), a_comp->m_scripts[i]));  
        }            
    }); 

    CanSerialize<Me::AI::AgentComponent>(eManager, a_entity, archive, [&archive](auto& a_comp)
    {                 
        archive(cereal::make_nvp("TargetLocation", a_comp->m_targetLocation.m_xyz)); 
        archive(cereal::make_nvp("AgentSpeed", a_comp->m_agentSpeed));
        archive(cereal::make_nvp("AgentStopDistance", a_comp->m_stopDistance));        
    });   

    archive.finishNode();
    archive.finishNode();
    archive.finishNode();
    
    return true;
}

bool Me::Serialization::Serializer::SerializeScene()
{
    return SerializeSceneA(m_activeScene);    
}

bool Me::Serialization::Serializer::SerializeSceneAs(std::string a_file)
{ 
    ms_instance->m_activeScene = a_file;
    return SerializeSceneA(a_file);    
}

bool Me::Serialization::Serializer::DeserializeScene(std::string a_file, bool a_rememberScene, bool a_cleanup)
{
    std::string path = a_file;
    if(path.empty())
    {
        path = ms_instance->m_activeScene;
    }
    else if(a_rememberScene)
    {
        ms_instance->m_activeScene = path;
    }

    std::ifstream is(path.c_str());
    is.open(path);

    if(!is.is_open())
    {
        return false;
    }

    cereal::XMLInputArchive archive(is);

    EntityManager* eManager = EntityManager::GetEntityManager();

    if (a_cleanup)
    {
        eManager->CleanGame();
    }
    
    int amount;

    archive.setNextName("SceneData"); 
    archive.startNode();  
    archive(cereal::make_nvp("EntityAmount", amount));
    archive.finishNode();
    
    for(int i = 0; i < amount;i++)
    {        
        archive.startNode();
        int compAmount = 0;
        archive(cereal::make_nvp("ComponentAmount", compAmount));
        archive.startNode(); 
        
        EntityID ent = eManager->CreateEntity();

        if(CanDeserialize<TagComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
        {
            std::string tag;
            archive(cereal::make_nvp("Tag", tag));
            a_comp->m_tag = tag;
            eManager->AddComponent(ent, a_comp);
        })) compAmount--;

        if(CanDeserialize<TransformComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
        {
            archive(cereal::make_nvp("Translation" , a_comp->m_translation.m_xyz));
            archive(cereal::make_nvp("Rotation" , a_comp->m_rotation.m_xyz));
            archive(cereal::make_nvp("Scale" , a_comp->m_scale.m_xyz));  
            eManager->AddComponent(ent, a_comp);
        })) compAmount--; 
        
        if(CanDeserialize<RenderComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
        {          
            archive(cereal::make_nvp("Colour", a_comp->m_colour.m_colour)); 
            std::string shaderPath;

            std::string mesh;
            archive(cereal::make_nvp("Mesh", mesh));

            if(!Files::FileSystem::GetFileExtention(mesh).empty())
            {                
                a_comp->m_mesh = Resources::MeshLibrary::CreateMesh(mesh);
            }
            else
            {
                a_comp->m_mesh = (Mesh)std::stoi(mesh);
            }

            archive(cereal::make_nvp("Shader", shaderPath));    
            a_comp->m_shader = Resources::ShaderLibrary::CreateShader(shaderPath);

            std::string texturePath;
            archive(cereal::make_nvp("Texture", texturePath));
            
            if(!texturePath.empty())  
                a_comp->m_texture = Resources::TextureLibrary::CreateTexture(texturePath);

            archive(cereal::make_nvp("UV", a_comp->m_textureCoords.m_xyzw));

            eManager->AddComponent(ent, a_comp);   

        })) compAmount--;

        if(CanDeserialize<CameraComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
        {          
            archive(cereal::make_nvp("Far", a_comp->m_far)); 
            archive(cereal::make_nvp("Near", a_comp->m_near)); 
            archive(cereal::make_nvp("Size", a_comp->m_size.m_xy)); 
            archive(cereal::make_nvp("OrthoScale", a_comp->m_orthoScale)); 
            archive(cereal::make_nvp("CameraLayer", a_comp->m_cameralayer)); 
            int type = 0;
            archive(cereal::make_nvp("CameraType", type)); 
            a_comp->m_cameraType = (CameraType)type;
            eManager->AddComponent(ent, a_comp); 
        })) compAmount--;             

        if(CanDeserialize<Physics::PhysicsComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
        {          
            archive(cereal::make_nvp("Gravity", a_comp->m_gravity));  
            archive(cereal::make_nvp("Body_Mass", a_comp->m_bodyMass)); 
            archive(cereal::make_nvp("Body_Drag", a_comp->m_drag));
            archive(cereal::make_nvp("Body_Friction", a_comp->m_friction));
            archive(cereal::make_nvp("DrawCollisionLines", a_comp->m_debugHitNormals));

            eManager->AddComponent(ent, a_comp); 
        })) compAmount;   

        if(CanDeserialize<Physics::BoxCollider2DComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
        {          
            archive(cereal::make_nvp("CollisionType", (Physics::CollisionType)a_comp->m_collisionType)); 
            archive(cereal::make_nvp("CollisionLayer", (uint16_t)a_comp->m_collisionLayer));  
            archive(cereal::make_nvp("CollisionScale", a_comp->m_colliderSize.m_xy)); 
            archive(cereal::make_nvp("CollisionOffset", a_comp->m_colliderOffset.m_xy)); 

            eManager->AddComponent(ent, a_comp); 
            eManager->AddComponent<DebugRenderComponent>(ent);
            
            Physics::ColliderTagComponent* cTag = new Physics::ColliderTagComponent(a_comp);
            eManager->AddComponent(ent, cTag);
        })) compAmount -= 3;   
        if (CanDeserialize<Physics::CircleColliderComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
        {
            archive(cereal::make_nvp("CollisionType", (Physics::CollisionType)a_comp->m_collisionType));
            archive(cereal::make_nvp("CollisionLayer", (uint16_t)a_comp->m_collisionLayer));
            archive(cereal::make_nvp("CollisionScale", a_comp->m_radius));
            archive(cereal::make_nvp("CollisionOffset", a_comp->m_colliderOffset.m_xy));

            eManager->AddComponent(ent, a_comp);
            eManager->AddComponent<DebugRenderComponent>(ent);

            Physics::ColliderTagComponent* cTag = new Physics::ColliderTagComponent(a_comp);
            eManager->AddComponent(ent, cTag);

        })) compAmount--;
        if(CanDeserialize<Physics::BoxCollider3DComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
        {          
            archive(cereal::make_nvp("CollisionType", (Physics::CollisionType)a_comp->m_collisionType)); 
            archive(cereal::make_nvp("CollisionLayer", (uint16_t)a_comp->m_collisionLayer));  
            archive(cereal::make_nvp("CollisionScale", a_comp->m_colliderSize.m_xyz)); 
            archive(cereal::make_nvp("CollisionOffset", a_comp->m_colliderOffset.m_xyz)); 

            eManager->AddComponent(ent, a_comp); 
            eManager->AddComponent<DebugRenderComponent>(ent);

            Physics::ColliderTagComponent* cTag = new Physics::ColliderTagComponent(a_comp);
            eManager->AddComponent(ent, cTag);

        })) compAmount -= 3;

        if(CanDeserialize<Physics::SphereColliderComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
        {          
            archive(cereal::make_nvp("CollisionType", (Physics::CollisionType)a_comp->m_collisionType)); 
            archive(cereal::make_nvp("CollisionLayer", (uint16_t)a_comp->m_collisionLayer));  
            archive(cereal::make_nvp("CollisionScale", a_comp->m_radius)); 
            archive(cereal::make_nvp("CollisionOffset", a_comp->m_colliderOffset.m_xyz)); 

            eManager->AddComponent(ent, a_comp); 
            eManager->AddComponent<DebugRenderComponent>(ent);

            Physics::ColliderTagComponent* cTag = new Physics::ColliderTagComponent(a_comp);
            eManager->AddComponent(ent, cTag);

        })) compAmount -= 3;    
        
        if(CanDeserialize<Scripting::ScriptComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
        {
            size_t size;
            archive(cereal::make_nvp("ScriptAmount", (size_t)size)); 

            for(size_t i = 0; i < size; i++)
            {
                std::string scriptPath = "ScriptPath" + std::to_string(i);
                std::string script;
                archive(cereal::make_nvp(scriptPath.c_str(), script));    
                a_comp->AddScript(script);
            }  
            
            eManager->AddComponent(ent, a_comp);
        })) compAmount--;

        if(CanDeserialize<Me::AI::AgentComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
        {
            archive(cereal::make_nvp("TargetLocation", a_comp->m_targetLocation.m_xyz)); 
            archive(cereal::make_nvp("AgentSpeed", a_comp->m_agentSpeed));
            archive(cereal::make_nvp("AgentStopDistance", a_comp->m_stopDistance));   
            eManager->AddComponent(ent, a_comp);
        })) compAmount--;

        archive.finishNode();    
        archive.finishNode();
    }

        
        
    ME_CORE_LOG("Finish Deserialize Scene \n");
    return false;    
}

bool Me::Serialization::Serializer::SerializeEntity(std::string a_path, EntityID a_entityId)
{
    return SerializeEntityA(a_path, a_entityId);
}

EntityID Me::Serialization::Serializer::DeserializeEntity(std::string a_file)
{
    std::string path = a_file;

    std::ifstream is(a_file.c_str());
    is.open(a_file);

    if(!is.is_open())
    {
        return 0;
    }

    cereal::XMLInputArchive archive(is);

    EntityManager* eManager = EntityManager::GetEntityManager();

    int compAmount = 0;

    archive.setNextName("PrefabData"); 
    archive.startNode();  
    
    archive.setNextName("Entity"); 
    archive.startNode();    

    std::string name;
    archive(cereal::make_nvp("EntityName" , name));
    archive(cereal::make_nvp("ComponentAmount", compAmount));
    archive.startNode(); 
    
    EntityID ent = eManager->CreateEntity();

    if(CanDeserialize<TagComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
    {
        std::string tag;
        archive(cereal::make_nvp("Tag", tag));
        a_comp->m_tag = tag;
        eManager->AddComponent(ent, a_comp);
    })) compAmount--;

    if(CanDeserialize<TransformComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
    {
        archive(cereal::make_nvp("Translation" , a_comp->m_translation.m_xyz));
        archive(cereal::make_nvp("Rotation" , a_comp->m_rotation.m_xyz));
        archive(cereal::make_nvp("Scale" , a_comp->m_scale.m_xyz));  
        eManager->AddComponent(ent, a_comp);
    })) compAmount--; 
    
    if(CanDeserialize<RenderComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
    {          
        archive(cereal::make_nvp("Colour", a_comp->m_colour.m_colour)); 
        std::string shaderPath;

        std::string mesh;
        archive(cereal::make_nvp("Mesh", mesh));

        if(!Files::FileSystem::GetFileExtention(mesh).empty())
        {                
            a_comp->m_mesh = Resources::MeshLibrary::CreateMesh(mesh);
        }
        else
        {
            a_comp->m_mesh = (Mesh)std::stoi(mesh);
        }

        archive(cereal::make_nvp("Shader", shaderPath));    
        a_comp->m_shader = Resources::ShaderLibrary::CreateShader(shaderPath);

        std::string texturePath;
        archive(cereal::make_nvp("Texture", texturePath));
        
        if(!texturePath.empty())  
            a_comp->m_texture = Resources::TextureLibrary::CreateTexture(texturePath);

        archive(cereal::make_nvp("UV", a_comp->m_textureCoords.m_xyzw));
        eManager->AddComponent(ent, a_comp);   

    })) compAmount--;

    if(CanDeserialize<CameraComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
    {          
        archive(cereal::make_nvp("Far", a_comp->m_far)); 
        archive(cereal::make_nvp("Near", a_comp->m_near)); 
        archive(cereal::make_nvp("Size", a_comp->m_size.m_xy)); 
        archive(cereal::make_nvp("OrthoScale", a_comp->m_orthoScale)); 
        archive(cereal::make_nvp("CameraLayer", a_comp->m_cameralayer)); 
        int type = 0;
        archive(cereal::make_nvp("CameraType", type)); 
        a_comp->m_cameraType = (CameraType)type;
        eManager->AddComponent(ent, a_comp); 
    })) compAmount--;             

    if(CanDeserialize<Physics::PhysicsComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
    {          
        archive(cereal::make_nvp("Gravity", a_comp->m_gravity)); 
        archive(cereal::make_nvp("Body_Mass", a_comp->m_bodyMass));
        archive(cereal::make_nvp("Body_Drag", a_comp->m_drag));
        archive(cereal::make_nvp("Body_Friction", a_comp->m_friction));
        archive(cereal::make_nvp("DrawCollisionLines", a_comp->m_debugHitNormals));

        eManager->AddComponent(ent, a_comp); 
    })) compAmount--;   

    if(CanDeserialize<Physics::BoxCollider2DComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
    {          
        archive(cereal::make_nvp("CollisionType", (Physics::CollisionType)a_comp->m_collisionType)); 
        archive(cereal::make_nvp("CollisionLayer", (uint16_t)a_comp->m_collisionLayer));  
        archive(cereal::make_nvp("CollisionScale", a_comp->m_colliderSize.m_xy)); 
        archive(cereal::make_nvp("CollisionOffset", a_comp->m_colliderOffset.m_xy)); 

        eManager->AddComponent(ent, a_comp); 
        eManager->AddComponent<DebugRenderComponent>(ent);
        
        Physics::ColliderTagComponent* cTag = new Physics::ColliderTagComponent(a_comp);
        eManager->AddComponent(ent, cTag);
    })) compAmount--;   
    if (CanDeserialize<Physics::CircleColliderComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
    {
        archive(cereal::make_nvp("CollisionType", (Physics::CollisionType)a_comp->m_collisionType));
        archive(cereal::make_nvp("CollisionLayer", (uint16_t)a_comp->m_collisionLayer));
        archive(cereal::make_nvp("CollisionScale", a_comp->m_radius));
        archive(cereal::make_nvp("CollisionOffset", a_comp->m_colliderOffset.m_xy));

        eManager->AddComponent(ent, a_comp);
        eManager->AddComponent<DebugRenderComponent>(ent);

        Physics::ColliderTagComponent* cTag = new Physics::ColliderTagComponent(a_comp);
        eManager->AddComponent(ent, cTag);

    })) compAmount--;
    if(CanDeserialize<Physics::BoxCollider3DComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
    {          
        archive(cereal::make_nvp("CollisionType", (Physics::CollisionType)a_comp->m_collisionType)); 
        archive(cereal::make_nvp("CollisionLayer", (uint16_t)a_comp->m_collisionLayer));  
        archive(cereal::make_nvp("CollisionScale", a_comp->m_colliderSize.m_xyz)); 
        archive(cereal::make_nvp("CollisionOffset", a_comp->m_colliderOffset.m_xyz)); 

        eManager->AddComponent(ent, a_comp); 
        eManager->AddComponent<DebugRenderComponent>(ent);

        Physics::ColliderTagComponent* cTag = new Physics::ColliderTagComponent(a_comp);
        eManager->AddComponent(ent, cTag);

    })) compAmount--; 

    if(CanDeserialize<Physics::SphereColliderComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
    {          
        archive(cereal::make_nvp("CollisionType", (Physics::CollisionType)a_comp->m_collisionType)); 
        archive(cereal::make_nvp("CollisionLayer", (uint16_t)a_comp->m_collisionLayer));  
        archive(cereal::make_nvp("CollisionScale", a_comp->m_radius)); 
        archive(cereal::make_nvp("CollisionOffset", a_comp->m_colliderOffset.m_xyz)); 

        eManager->AddComponent(ent, a_comp); 
        eManager->AddComponent<DebugRenderComponent>(ent);

        Physics::ColliderTagComponent* cTag = new Physics::ColliderTagComponent(a_comp);
        eManager->AddComponent(ent, cTag);

    })) compAmount--;     
    
    if(CanDeserialize<Scripting::ScriptComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
    {
        size_t size;
        archive(cereal::make_nvp("ScriptAmount", (size_t)size)); 

        for(size_t i = 0; i < size; i++)
        {
            std::string scriptPath = "ScriptPath" + std::to_string(i);
            std::string script;
            archive(cereal::make_nvp(scriptPath.c_str(), script));  
            a_comp->AddScript(script);
        } 

        eManager->AddComponent(ent, a_comp);
    })) compAmount--;

    if(CanDeserialize<Me::AI::AgentComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
    {
        archive(cereal::make_nvp("TargetLocation", a_comp->m_targetLocation.m_xyz)); 
        archive(cereal::make_nvp("AgentSpeed", a_comp->m_agentSpeed));
        archive(cereal::make_nvp("AgentStopDistance", a_comp->m_stopDistance));   
        eManager->AddComponent(ent, a_comp);
    })) compAmount--;

    archive.finishNode();
    archive.finishNode();
    archive.finishNode(); 

    return ent;
}