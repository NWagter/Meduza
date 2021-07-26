#include "PCH.h"

#include "Games/Physics2D/Physics2D.h"

#include "MeduzaIncluder.h"

#include "Systems/Physics2D/OverlapSystem.h"

Physics::Physics2D::Physics2D()
{
    m_gameName = "Physics Test";

}
Physics::Physics2D::~Physics2D()
{

}

void Physics::Physics2D::InitGame()
{
    new OverlapSystem();
    auto eManager = Me::EntityManager::GetEntityManager();

    auto cC = new Me::CameraComponent();
    cC->m_cameraType = Me::CameraType::Orthographic;
    cC->m_near = 0.0f;
    cC->m_far = 100;
    cC->m_size = Me::Event::EventSystem::GetEventSystem()->ScreenSize();

    EntityID entCam = Me::EntityManager::CreateEntity();
    eManager->AddComponent<Me::CameraComponent>(entCam, cC);
    eManager->AddComponent<Me::TransformComponent>(entCam);

    SetupScene();
}

void Physics::Physics2D::UpdateGame(float)
{
    auto eSystem = Me::Event::EventSystem::GetEventSystem();

    if(eSystem->KeyDown(Me::Event::KeyCode::Space))
    {
        SpawnObjects();
    }
}

void Physics::Physics2D::SetupScene()
{
    
    auto eManager = Me::EntityManager::GetEntityManager(); 

    Me::Shader mesh = Me::Resources::MeshLibrary::GetMeshIndex(Me::Primitives::Quad);
    Me::Shader shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/UnlitColour_Shader.hlsl");
   
    if(shader == 0)
    {      
        shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/UnlitColour_Shader.glsl");
    }

    EntityID box2d2 = Me::EntityManager::CreateEntity();

    auto rC2 = new Me::RenderComponent();
    auto tC2 = new Me::TransformComponent();
    auto pC2 = new Me::Physics::PhysicsComponent();

    rC2->m_colour = Me::Colours::RED;
    rC2->m_shader = shader;
    rC2->m_mesh = mesh;

    Me::Math::Vec3 position2;

    position2.m_x = static_cast<float>(0);
    position2.m_y = static_cast<float>(-128);
    position2.m_z = 2;
    tC2->SetPosition(position2);
    tC2->SetUniformScale(static_cast<float>(32));
    
    pC2->m_body->m_uniformScale = 32;
    pC2->m_gravity = false;
    pC2->m_physicsLayerId = 1;

    eManager->AddComponent<Me::RenderComponent>(box2d2, rC2);
    eManager->AddComponent<Me::TransformComponent>(box2d2, tC2);
    eManager->AddComponent<Me::Physics::PhysicsComponent>(box2d2, pC2);
}

void Physics::Physics2D::SpawnObjects()
{      
    auto eManager = Me::EntityManager::GetEntityManager(); 

    Me::Shader mesh = Me::Resources::MeshLibrary::GetMeshIndex(Me::Primitives::Quad);
    Me::Shader shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/UnlitColour_Shader.hlsl");
   
    if(shader == 0)
    {      
        shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/UnlitColour_Shader.glsl");
    }

    EntityID box2d = Me::EntityManager::CreateEntity();
    auto rC = new Me::RenderComponent();
    auto tC = new Me::TransformComponent();
    auto pC = new Me::Physics::PhysicsComponent();
    
    rC->m_colour = Me::Colours::AZURE_WHITE;
    rC->m_shader = shader;
    rC->m_mesh = mesh;

    Me::Math::Vec3 position;

    position.m_x = static_cast<float>(0);
    position.m_y = static_cast<float>(128);
    position.m_z = 2;

    tC->SetPosition(position);
    tC->SetUniformScale(static_cast<float>(32));

    pC->m_collisionType = Me::Physics::CollisionType::Block;
    pC->m_body->m_uniformScale = 32;

    eManager->AddComponent<Me::RenderComponent>(box2d, rC);
    eManager->AddComponent<Me::TransformComponent>(box2d, tC);
    eManager->AddComponent<Me::Physics::PhysicsComponent>(box2d, pC);



    EntityID box2d3 = Me::EntityManager::CreateEntity();

    auto rC3 = new Me::RenderComponent();
    auto tC3 = new Me::TransformComponent();
    auto pC3 = new Me::Physics::PhysicsComponent();

    rC3->m_colour = Me::Colours::RED;
    rC3->m_shader = shader;
    rC3->m_mesh = mesh;

    Me::Math::Vec3 position3;

    position3.m_x = static_cast<float>(0);
    position3.m_y = static_cast<float>(256);
    position3.m_z = 2;

    tC3->SetPosition(position3);
    tC3->SetUniformScale(static_cast<float>(32));
    
    pC3->m_collisionType = Me::Physics::CollisionType::Overlap;
    pC3->m_body->m_uniformScale = 32;
    pC3->m_gravity = true;

    eManager->AddComponent<Me::RenderComponent>(box2d3, rC3);
    eManager->AddComponent<Me::TransformComponent>(box2d3, tC3);
    eManager->AddComponent<Me::Physics::PhysicsComponent>(box2d3, pC3);
}