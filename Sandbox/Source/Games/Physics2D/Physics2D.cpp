#include "PCH.h"

#include "Games/Physics2D/Physics2D.h"

#include "MeduzaIncluder.h"

Physics::Physics2D::Physics2D()
{
    m_gameName = "Physics Test";

}
Physics::Physics2D::~Physics2D()
{

}

void Physics::Physics2D::InitGame()
{
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

void Physics::Physics2D::SetupScene()
{
    
    auto eManager = Me::EntityManager::GetEntityManager();

    EntityID box2d = Me::EntityManager::CreateEntity();

    auto rC = new Me::RenderComponent();
    auto tC = new Me::TransformComponent();
    auto pC = new Me::Physics::PhysicsComponent();

    Me::Shader mesh = Me::Resources::MeshLibrary::GetMeshIndex(Me::Primitives::Quad);
    Me::Shader shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/UnlitColour_Shader.hlsl");
   
    if(shader == 0)
    {      
        shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/Default_Shader.glsl");
    }

    rC->m_colour = Me::Colours::AZURE_WHITE;
    rC->m_shader = shader;
    rC->m_mesh = mesh;

    tC->m_position.m_x = static_cast<float>(0);
    tC->m_position.m_y = static_cast<float>(0);
    tC->m_position.m_z = 2;
    tC->m_uniformScale = static_cast<float>(32);

    pC->m_body->m_uniformScale = 32;

    eManager->AddComponent<Me::RenderComponent>(box2d, rC);
    eManager->AddComponent<Me::TransformComponent>(box2d, tC);
    eManager->AddComponent<Me::Physics::PhysicsComponent>(box2d, pC);

    EntityID box2d2 = Me::EntityManager::CreateEntity();

    auto rC2 = new Me::RenderComponent();
    auto tC2 = new Me::TransformComponent();
    auto pC2 = new Me::Physics::PhysicsComponent();

    rC2->m_colour = Me::Colours::BLACK;
    rC2->m_shader = shader;
    rC2->m_mesh = mesh;

    tC2->m_position.m_x = static_cast<float>(0);
    tC2->m_position.m_y = static_cast<float>(-128);
    tC2->m_position.m_z = 2;
    tC2->m_uniformScale = static_cast<float>(32);
    
    pC2->m_body->m_uniformScale = 32;
    pC2->m_gravity = false;

    eManager->AddComponent<Me::RenderComponent>(box2d2, rC2);
    eManager->AddComponent<Me::TransformComponent>(box2d2, tC2);
    eManager->AddComponent<Me::Physics::PhysicsComponent>(box2d2, pC2);

    EntityID box2d3 = Me::EntityManager::CreateEntity();

    auto rC3 = new Me::RenderComponent();
    auto tC3 = new Me::TransformComponent();
    auto pC3 = new Me::Physics::PhysicsComponent();

    rC3->m_colour = Me::Colours::RED;
    rC3->m_shader = shader;
    rC3->m_mesh = mesh;

    tC3->m_position.m_x = static_cast<float>(0);
    tC3->m_position.m_y = static_cast<float>(128);
    tC3->m_position.m_z = 2;
    tC3->m_uniformScale = static_cast<float>(32);
    
    pC3->m_body->m_uniformScale = 32;
    pC3->m_gravity = true;

    eManager->AddComponent<Me::RenderComponent>(box2d3, rC3);
    eManager->AddComponent<Me::TransformComponent>(box2d3, tC3);
    eManager->AddComponent<Me::Physics::PhysicsComponent>(box2d3, pC3);
}