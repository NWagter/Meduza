#include "PCH.h"
#include "Systems/CursorSystem.h"

#include "MeduzaIncluder.h"
#include "Components/CursorComponent.h"

CursorSystem::CursorSystem()
{

}

void CursorSystem::OnCreate()
{
    auto quad = Me::Resources::MeshLibrary::GetMeshIndex(Me::Primitives::Quad);
    auto shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/FlatColour_Shader.hlsl");

    auto eManager = Me::EntityManager::GetEntityManager();

    auto entt = Me::EntityManager::CreateEntity();
    auto tC = new Me::TransformComponent();
    auto rC = new Me::RenderComponent();
    auto cC = new CursorComponent();

    rC->m_mesh = quad;
    rC->m_colour = Me::Colours::GREEN;
    rC->m_shader = shader;

    tC->m_uniformScale = 8;

    eManager->AddComponent<CursorComponent>(entt, cC);
    eManager->AddComponent<Me::RenderComponent>(entt, rC);     
    eManager->AddComponent<Me::TransformComponent>(entt, tC);
}

void CursorSystem::OnUpdate(float a_time)
{
    Me::Math::Vec2 mPos = Me::Event::EventSystem::GetEventSystem()->MousePosition();

    for(auto& compTuple : m_components)
    {
        CursorComponent* cC = std::get<CursorComponent*>(compTuple);
        if(cC == nullptr)
        {
            continue;
        }

        Me::TransformComponent* tC = std::get<Me::TransformComponent*>(compTuple);
        
        tC->m_position = cC->m_position = Me::Math::Vec3(mPos.m_x, mPos.m_y, 1);
    }
}