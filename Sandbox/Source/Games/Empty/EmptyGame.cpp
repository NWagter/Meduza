#include "PCH.h"

#include "Games/Empty/EmptyGame.h"

#include "MeduzaIncluder.h"

#include "Components/RotateComponent.h"
#include "Systems/Rotator.h"

EmptyGame::EmptyGame()
{
   m_gameName = "Empty"; 

   new Rotator();
}

EmptyGame::~EmptyGame()
{

}

void EmptyGame::InitGame()
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

    Me::Shader mesh = Me::Resources::MeshLibrary::GetMeshIndex(Me::Primitives::Cube);
    Me::Shader shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/FlatColourLighted_Shader.hlsl");

    EntityID cube = eManager->CreateEntity();
    Me::RenderComponent* rComp = new Me::RenderComponent();
    Me::TransformComponent* tComp = new Me::TransformComponent();
    RotateComponent* rotComp = new RotateComponent();

    tComp->m_position.m_x = static_cast<float>(0);
    tComp->m_position.m_y = static_cast<float>(0);
    tComp->m_position.m_z = 200;
    tComp->m_uniformScale = static_cast<float>(20);

    rotComp->m_rotateSpeed = 0.25f;

    rComp->m_mesh = mesh;
    rComp->m_shader = shader;
    rComp->m_colour = Me::Colours::CELESTIAL_BLUE;

    eManager->AddComponent<RotateComponent>(cube, rotComp);
    eManager->AddComponent<Me::RenderComponent>(cube, rComp);
    eManager->AddComponent<Me::TransformComponent>(cube, tComp);
}