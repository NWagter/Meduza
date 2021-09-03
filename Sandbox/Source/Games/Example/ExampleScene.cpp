#include "PCH.h"

#include "Games/Example/ExampleScene.h"

#include "MeduzaIncluder.h"

#include "Systems/CameraControllerSystem.h"
#include "Systems/Rotator.h"

#include "Components/RotateComponent.h"

ExampleScene::ExampleScene()
{    
   m_gameName = "Example"; 

   new CameraControllerSystem();
   new Rotator();
}

ExampleScene::~ExampleScene()
{
    
}

void ExampleScene::InitGame()
{
    auto eManager = Me::EntityManager::GetEntityManager();

    auto cC = new Me::CameraComponent();
    cC->m_cameraType = Me::CameraType::Perspective;
    cC->m_near = 0.1f;
    cC->m_far = 1000;
    cC->m_size = Me::Event::EventSystem::GetEventSystem()->ScreenSize();

    EntityID entCam = Me::EntityManager::CreateEntity();
    eManager->AddComponent<Me::CameraComponent>(entCam, cC);
    eManager->AddComponent<Me::TransformComponent>(entCam);

    CreateFloor(*eManager);

    Me::Math::Vec3 position = Me::Math::Vec3(0, 0, 10);
    Me::Math::Vec3 rotation = Me::Math::Vec3(0,0,0);   
    rotation.m_y = 180;

    Me::Mesh suzanne = Me::Resources::MeshLibrary::CreateMesh("Assets/Models/Suzanne/Suzanne.gltf");
    Me::Texture suzanneTexture = Me::Resources::TextureLibrary::GetTexture("Assets/Models/Suzanne/Suzanne_BaseColor.png");

    Me::Shader shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/Lit_Shader.hlsl");
    if(shader == 0)
    {      
        shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/Lit_Shader.glsl");
    }

    EntityID suzanneEntt = eManager->CreateEntity();
    Me::RenderComponent* rComp = new Me::RenderComponent();
    Me::TransformComponent* tComp = new Me::TransformComponent();
    RotateComponent* rotComp = new RotateComponent();

    tComp->m_translation = position;
    tComp->m_rotation  = rotation;
    tComp->m_scale = Me::Math::Vec3(1.0f);

    rComp->m_mesh = suzanne;
    rComp->m_shader = shader;
    rComp->m_colour = Me::Colours::WHITE;
    rComp->m_texture = suzanneTexture;

    rotComp->m_rotateSpeed = 10.0f;

    eManager->AddComponent<Me::RenderComponent>(suzanneEntt, rComp);
    eManager->AddComponent<Me::TransformComponent>(suzanneEntt, tComp);
    eManager->AddComponent<RotateComponent>(suzanneEntt, rotComp);
}

void ExampleScene::UpdateGame(float)
{
}

void ExampleScene::CreateFloor(Me::EntityManager& a_eManager)
{
    Me::Mesh mesh = Me::Resources::MeshLibrary::GetMeshIndex(Me::Primitives::Plane);    
    Me::Shader shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/Lit_Shader.hlsl");    
    Me::Texture texture = Me::Resources::TextureLibrary::CreateTexture("Assets/Textures/DefaultTex.png");

    if(shader == 0)
    {      
        shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/Lit_Shader.glsl");
    }

    EntityID cube = a_eManager.CreateEntity();
    Me::RenderComponent* rComp = new Me::RenderComponent();
    Me::TransformComponent* tComp = new Me::TransformComponent();

    rComp->m_mesh = mesh;
    rComp->m_shader = shader;
    rComp->m_texture = texture;
    rComp->m_colour = Me::Colours::WHITE;

    Me::Math::Vec3 pos = Me::Math::Vec3(0,-2,10);

    tComp->m_translation = pos;
    tComp->m_scale  = Me::Math::Vec3(10.0f);

    a_eManager.AddComponent<Me::RenderComponent>(cube, rComp);
    a_eManager.AddComponent<Me::TransformComponent>(cube, tComp);
}