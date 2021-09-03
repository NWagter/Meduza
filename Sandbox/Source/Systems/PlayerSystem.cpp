#include "PCH.h"
#include "Systems/PlayerSystem.h"

#include "MeduzaIncluder.h"

PlayerSystem::PlayerSystem()
{

}

void PlayerSystem::OnCreate()
{
    auto ent = Me::EntityManager::CreateEntity();
    auto pC = new PlayerComponent();

    auto entList = Me::EntityManager::GetEntityManager()->GetEntities();
    for(auto entt : entList)
    {
        if(entt.second.find(Me::CameraComponent::s_componentID) != entt.second.end())
        {
            pC->m_cameraTransform = Me::EntityManager::GetEntityManager()->GetComponent<Me::TransformComponent>(entt.first);
            break;
        }
    }

    for(auto entt : entList)
    {
        if(entt.second.find(CursorComponent::s_componentID) != entt.second.end())
        {            
            pC->m_cursorComponent = Me::EntityManager::GetEntityManager()->GetComponent<CursorComponent>(entt.first);
            break;
        }
    }
    
    Me::EntityManager::GetEntityManager()->AddComponent<PlayerComponent>(ent, pC);
}

void PlayerSystem::OnUpdate(float a_dt)
{
    Me::Math::Vec2 mousePos = Me::Event::EventSystem::GetEventSystem()->MousePosition();

    for(auto& compTuple : m_components)
    {          
        PlayerComponent* pC = std::get<PlayerComponent*>(compTuple);  

        Me::Math::Vec3 camPos = pC->m_cameraTransform->m_translation;

        pC->m_cursorComponent->m_position = (Me::Math::Vec3(mousePos.m_x, mousePos.m_y, camPos.m_z) - camPos);
    }
}