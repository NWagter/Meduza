#include "PCH.h"
#include "Systems/CheckerboardSystem.h"

#include "MeduzaIncluder.h"

#include "Components/PlayerComponent.h"
#include "Components/CursorComponent.h"
#include "Components/PawnComponent.h"

static char chars[] =
{
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'
};

CheckboardSystem::CheckboardSystem()
{

}

void CheckboardSystem::OnCreate()
{
    CreateBoard();

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
    bool onLeftClick = false;
    PlayerComponent* player;

    if(Me::Event::EventSystem::GetEventSystem()->MouseButtonDown(Me::Event::MouseButton::LButton))
    {
        onClick = true;
        onLeftClick = true;
        player = Me::EntityManager::GetEntityManager()->GetComponent<PlayerComponent>(m_playerEntity);
        Me::Math::Vec3 cPos = player->m_cursorComponent->m_position;
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
                auto pawn = tileC->m_pawn;

                if(player->m_selectedPawn != nullptr)
                {
                    auto selectedPawn = player->m_selectedPawn;
                    if(pawn == nullptr)
                    {
                        //Can move here!
                        selectedPawn->m_newPos = tPos;
                        selectedPawn->m_moving = true;
                        tileC->m_pawn = selectedPawn;
                        selectedPawn->m_tile->m_pawn = nullptr;
                        selectedPawn->m_tile = tileC;
                        
                    }

                    player->m_selectedPawn = nullptr;
                }

                if(pawn != nullptr && player != nullptr)
                {
                    if(pawn->m_colour == PawnColour::Black)
                    {
                        printf("You can't selected : %s of colour (Black) \n ", GetPieceName(pawn->m_type).c_str());                        
                    }
                    else
                    {
                        if(!pawn->m_moving)
                        {
                            printf("You selected : %s \n ", GetPieceName(pawn->m_type).c_str());
                            player->m_selectedPawn = pawn;
                        }
                    }
                }

                onClick = false;
                continue;
            }
        }
    }
}

void CheckboardSystem::CreateBoard()
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
            tileC->m_char = chars[x];
            tileC->m_pawn = CreatePieces(y, x);
            if(tileC->m_pawn != nullptr)
            {
                tileC->m_pawn->m_tile = tileC;
            }
            black = !black;

            eManager->AddComponent<Me::RenderComponent>(entt, rC);     
            eManager->AddComponent<Me::TransformComponent>(entt, tC);
            eManager->AddComponent<TileComponent>(entt, tileC);
        }

        black = !black;
    }

}

PawnComponent* CheckboardSystem::CreatePieces(int a_row, int a_col)
{
    int r = a_row + 1;
    
    if(r < 7 && r > 2)
    {
        return nullptr;
    }

    auto eManager = Me::EntityManager::GetEntityManager();

    auto quad = Me::Resources::MeshLibrary::GetMeshIndex(Me::Primitives::Quad);
    auto texture = Me::Resources::TextureLibrary::CreateTexture("Assets/Textures/ChessPieces.png");
    auto shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/Default_Shader.hlsl");

    auto entt = Me::EntityManager::CreateEntity();

    auto tC = new Me::TransformComponent();
    auto rC = new Me::RenderComponent();
    auto pC = new PawnComponent();

    tC->m_position = Me::Math::Vec3((a_col * 32),(a_row * 32),  9);
    tC->m_uniformScale = 32;

    rC->m_shader = shader;
    rC->m_mesh = quad;
    rC->m_texture = texture;

    if(r == 2 || r == 7)
    {
        //Set Pawn Texture
        pC->m_type = PawnTypes::Pawn;
        rC->m_textureCoords = Me::Utils::TextureSlice(  Me::Math::Vec2(1024,170),
                                                        Me::Math::Vec2(850,0),
                                                        Me::Math::Vec2(170,170));

        if(r == 2)
        {        
            rC->m_colour = Me::Colours::GREEN;
            pC->m_colour = PawnColour::White;
        }
        else
        {
            rC->m_colour = Me::Colours::RED;
            pC->m_colour = PawnColour::Black;
        }
    }

    if(r == 1 || r == 8)
    {
        //Set Texture
        switch (a_col)
        {
        case 0: case 7:
            pC->m_type = PawnTypes::Rook;
            rC->m_textureCoords = Me::Utils::TextureSlice(  Me::Math::Vec2(1024,170),
                                                            Me::Math::Vec2(680,0),
                                                            Me::Math::Vec2(170,170));
            
            break;            
        case 1: case 6: 
            pC->m_type = PawnTypes::Knight;
            rC->m_textureCoords = Me::Utils::TextureSlice(  Me::Math::Vec2(1024,170),
                                                            Me::Math::Vec2(510,0),
                                                            Me::Math::Vec2(170,170));
            break;            
        case 2: case 5:
            pC->m_type = PawnTypes::Bishop;
            rC->m_textureCoords = Me::Utils::TextureSlice(  Me::Math::Vec2(1024,170),
                                                            Me::Math::Vec2(340,0),
                                                            Me::Math::Vec2(170,170));
            break;            
        case 3:
            pC->m_type = PawnTypes::Queen;
            rC->m_textureCoords = Me::Utils::TextureSlice(  Me::Math::Vec2(1024,170),
                                                            Me::Math::Vec2(170,0),
                                                            Me::Math::Vec2(170,170));
            break;            
        case 4:
            pC->m_type = PawnTypes::King;
            rC->m_textureCoords = Me::Utils::TextureSlice(  Me::Math::Vec2(1024,170),
                                                            Me::Math::Vec2(0,0),
                                                            Me::Math::Vec2(170,170));
            break;
        }

        if(r == 1)
        {
            rC->m_colour = Me::Colours::GREEN;  
            pC->m_colour = PawnColour::White;
        } 
        else
        {
            pC->m_colour = PawnColour::Black;
            rC->m_colour = Me::Colours::RED;
        }    
    }   

    
    eManager->AddComponent<Me::RenderComponent>(entt, rC);  
    eManager->AddComponent<Me::TransformComponent>(entt, tC);
    eManager->AddComponent<PawnComponent>(entt, pC);

    return pC;
}

std::string CheckboardSystem::GetPieceName(PawnTypes a_type)
{
    switch (a_type)
    {
    case PawnTypes::Pawn :
        return "Pawn";
        break;
    case PawnTypes::Bishop :
        return "Bishop";
        break;
    case PawnTypes::Rook :
        return "Rook";
        break;
    case PawnTypes::Knight :
        return "Knight";
        break;
    case PawnTypes::Queen :
        return "Queen";
        break;
    case PawnTypes::King :
        return "King";
        break;
    }

    return "";
}