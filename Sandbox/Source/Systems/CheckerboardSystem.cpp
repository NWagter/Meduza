#include "PCH.h"
#include "Systems/CheckerboardSystem.h"

#include "MeduzaIncluder.h"

#include "Components/PlayerComponent.h"
#include "Components/CursorComponent.h"

CheckboardSystem::CheckboardSystem()
{

}

void CheckboardSystem::OnCreate()
{
    auto quad = Me::Resources::MeshLibrary::GetMeshIndex(Me::Primitives::Quad);
    auto shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/FlatColour_Shader.hlsl");
    auto eManager = Me::EntityManager::GetEntityManager();

    if(shader == 0)
    {
        Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/Default_Shader.glsl");
    }

    bool black = true;
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            auto entt = Me::EntityManager::CreateEntity();
            auto tC = new Me::TransformComponent();
            auto rC = new Me::RenderComponent();
            auto tileC = new TileComponent();

            tC->m_position = Me::Math::Vec3(x * 32, y * 32 , 10);
            tC->m_uniformScale = 32;
            
            rC->m_mesh = quad;
            rC->m_shader = shader;
            if(black)
            {
                rC->m_colour = Me::Colours::BLACK;
            }
            else
            {
                rC->m_colour = Me::Colours::WHITE;

            }
            tileC->m_tileId = y + 1;
            black = !black;

            eManager->AddComponent<Me::RenderComponent>(entt, rC);     
            eManager->AddComponent<Me::TransformComponent>(entt, tC);
            eManager->AddComponent<TileComponent>(entt, tileC);
        }

        black = !black;
    }


    auto entList = Me::EntityManager::GetEntityManager()->GetEntities();
    EntityID curEnt = 0;
    for(auto entt : entList)
    {
        if(entt.second.find(PlayerComponent::s_componentID) != entt.second.end())
        {            
            curEnt = entt.first;
            break;
        }
    }
    m_playerEntity = curEnt;
}

void CheckboardSystem::OnUpdate(float)
{    
    Me::Math::Vec2 pos;

    bool onClick = false;

    if(Me::Event::EventSystem::GetEventSystem()->MouseButtonDown(Me::Event::MouseButton::LButton))
    {
        onClick = true;
        Me::Math::Vec3 cPos = Me::EntityManager::GetEntityManager()->GetComponent<PlayerComponent>(m_playerEntity)->m_cursorComponent->m_position;
        pos = Me::Math::Vec2(cPos.m_x, cPos.m_y);
    }

    for(auto& compTuple : m_components)
    {
        if(onClick)
        {
            Me::TransformComponent* tC = std::get<Me::TransformComponent*>(compTuple);
            auto tPos = tC->m_position;
            
            if((pos.m_x > tPos.m_x && pos.m_x < (tPos.m_x + tC->m_uniformScale))
                && (pos.m_y > tPos.m_y && pos.m_y < (tPos.m_y + tC->m_uniformScale)))
            {           
                TileComponent* tileC = std::get<TileComponent*>(compTuple);

                printf("You selected tile : %i \n", tileC->m_tileId);
            }


        }
    }
}