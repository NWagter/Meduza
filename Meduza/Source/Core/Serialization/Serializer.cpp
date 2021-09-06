#include "MePCH.h"
#include "Core/Serialization/Serializer.h"

#include "ECS/EntityManager.h"

#include "Core/Components/TransformComponent.h"
#include "Core/Components/RenderComponent.h"
#include "Core/Components/CameraComponent.h"

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

    if(!a_file.empty())
    {

    }

    ms_instance = this;
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
    auto comp = new T();

    if(a_archive.getNodeName() == nullptr)
    {
        return false;
    }

    if(std::to_string(T::s_componentID) == a_archive.getNodeName())
    {
        a_archive.startNode(); 
        a_function(comp);
        a_archive.finishNode();

        return true;
    }

    return false;
}

bool Me::Serialization::Serializer::SerializeScene(std::string a_file)
{
    EntityManager* eManager = EntityManager::GetEntityManager();

    std::ofstream os(a_file.c_str());
    cereal::XMLOutputArchive archive(os);

    archive.setNextName("SceneData"); 
    archive.startNode();  
    archive(cereal::make_nvp("EntityAmount" , (uint64_t)eManager->GetEntities().size()));
    archive.finishNode();

    for (auto ent : eManager->GetEntities())
    {     
        archive.setNextName("Entity"); 
        archive.startNode();    
        archive(cereal::make_nvp("EntityID" ,ent.first));
        archive.setNextName("Components"); 
        archive(cereal::make_nvp("ComponentAmount" , (int)ent.second.size()));

        archive.startNode(); 
        CanSerialize<TagComponent>(eManager, ent.first, archive, [&archive](auto& a_comp)
        {  
            archive(cereal::make_nvp("Tag", a_comp->m_tag));
        });        
        
        CanSerialize<TransformComponent>(eManager, ent.first, archive, [&archive](auto& a_comp)
        {          
            archive(cereal::make_nvp("Translation", a_comp->m_translation.m_xyz));
            archive(cereal::make_nvp("Rotation", a_comp->m_rotation.m_xyz));
            archive(cereal::make_nvp("Scale", a_comp->m_scale.m_xyz));
            
        });   

        CanSerialize<RenderComponent>(eManager, ent.first, archive, [&archive](auto& a_comp)
        {          
            archive(cereal::make_nvp("Colour", a_comp->m_colour.m_colour));   

            if(a_comp->m_mesh > 10)
            {
                auto mesh = Resources::MeshLibrary::GetMesh(a_comp->m_mesh);  
                archive(cereal::make_nvp("Mesh", mesh->GetPath()));   
            }   
            else
            {
                archive(cereal::make_nvp("Mesh", a_comp->m_mesh)); 
            }

            auto shader = Resources::ShaderLibrary::GetShader(a_comp->m_shader);
            archive(cereal::make_nvp("Shader", shader->GetPath()));    
            auto texture = Resources::TextureLibrary::GetTexture(a_comp->m_texture);
            if(texture != nullptr)
            {
                archive(cereal::make_nvp("Texture", texture->GetPath())); 
            } 
            else            
            {
                archive(cereal::make_nvp("Texture", ""));  
            }
        });   

        CanSerialize<CameraComponent>(eManager, ent.first, archive, [&archive](auto& a_comp)
        {          
            archive(cereal::make_nvp("Far", a_comp->m_far)); 
            archive(cereal::make_nvp("Near", a_comp->m_near)); 
            archive(cereal::make_nvp("Size", a_comp->m_size.m_xy)); 
            archive(cereal::make_nvp("OrthoScale", a_comp->m_orthoScale)); 
            archive(cereal::make_nvp("CameraType", (int)a_comp->m_cameraType));           
        }); 

        archive.finishNode();
    }
    return false;
    
}

bool Me::Serialization::Serializer::DeserializeScene(std::string a_file)
{
    std::ifstream is(a_file.c_str());

    is.open(a_file);

    if(!is.is_open())
    {
        return false;
    }

    cereal::XMLInputArchive archive(is);

    EntityManager* eManager = EntityManager::GetEntityManager();
    int amount;

    archive.setNextName("SceneData"); 
    archive.startNode();  
    archive(cereal::make_nvp("EntityAmount", amount));
    archive.finishNode();
    
    for(int i = 0; i < amount;i++)
    {        
        archive.startNode();
        int compAmount = 0;
        EntityID entId;
        archive(cereal::make_nvp("EntityID" , entId));
        archive(cereal::make_nvp("ComponentAmount", compAmount));
        archive.startNode(); 
        
        EntityID ent;

        if(CanDeserialize<TagComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
        {
            std::string tag;
            archive(cereal::make_nvp("Tag", tag));
            ent = eManager->CreateEntity(tag);
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

            eManager->AddComponent(ent, a_comp);   

        })) compAmount--;

        if(CanDeserialize<CameraComponent>(archive, [&ent, &eManager, &archive](auto& a_comp)
        {          
            archive(cereal::make_nvp("Far", a_comp->m_far)); 
            archive(cereal::make_nvp("Near", a_comp->m_near)); 
            archive(cereal::make_nvp("Size", a_comp->m_size.m_xy)); 
            archive(cereal::make_nvp("OrthoScale", a_comp->m_orthoScale)); 
            archive(cereal::make_nvp("CameraType", (CameraType)a_comp->m_cameraType)); 
            eManager->AddComponent(ent, a_comp); 
        })) compAmount--;             


        archive.finishNode();
    }

    return false;    
}