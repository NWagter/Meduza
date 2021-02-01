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
}