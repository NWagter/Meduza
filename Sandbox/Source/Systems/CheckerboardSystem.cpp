#include "PCH.h"
#include "Systems/ChessboardSystem.h"

#include "MeduzaIncluder.h"

#include "Components/PlayerComponent.h"
#include "Components/CursorComponent.h"
#include "Components/PawnComponent.h"

static char chars[] =
{
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'
};

ChessboardSystem::ChessboardSystem()
{

}

void ChessboardSystem::OnCreate()
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

void ChessboardSystem::OnUpdate(float)
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
            auto tSize = tC->m_uniformScale / 2;
            
            if( (pos.m_x > tPos.m_x - tSize && pos.m_x < tPos.m_x + tSize) &&
                (pos.m_y > tPos.m_y - tSize && pos.m_y < tPos.m_y + tSize))
            {           
                TileComponent* tileC = std::get<TileComponent*>(compTuple);

                if(player->m_selectedPawn != nullptr)
                {
                    auto selectedPawn = player->m_selectedPawn;
                    if(CheckMove(selectedPawn, tileC))
                    {
                        if(!selectedPawn->m_hasMoved)
                        {
                            //Required for Pawn
                            selectedPawn->m_hasMoved = true;
                        }

                        selectedPawn->m_newPos = tPos;
                        selectedPawn->m_newPos.m_z = 9;
                        selectedPawn->m_moving = true;
                        tileC->m_pawn = selectedPawn;
                        selectedPawn->m_tile->m_pawn = nullptr;
                        selectedPawn->m_tile = tileC;
                        
                    }

                    player->m_selectedPawn = nullptr;
                    break;
                }              
                else
                {
                    auto pawn = tileC->m_pawn;
                    if(pawn != nullptr && !pawn->m_moving)
                    {
                        printf("You selected : %s \n ", GetPieceName(pawn->m_type).c_str());
                        player->m_selectedPawn = pawn;
                    }
                }

                onClick = false;
                continue;
            }
        }
    }
}

void ChessboardSystem::CreateBoard()
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

            tileC->m_tileX = x;
            tileC->m_tileY = y;

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

PawnComponent* ChessboardSystem::CreatePieces(int a_row, int a_col)
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

std::string ChessboardSystem::GetPieceName(PawnTypes a_type)
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

bool ChessboardSystem::CheckMove(PawnComponent* a_pawn, TileComponent* a_destination)
{
    if(a_destination->m_pawn != nullptr && a_destination->m_pawn->m_colour == a_pawn->m_colour)
    {
        return false;
    }

    PawnTypes pType = a_pawn->m_type;
    auto originTile = a_pawn->m_tile;

    Me::Math::Vec2 origin = Me::Math::Vec2(originTile->m_tileX, originTile->m_tileY);
    Me::Math::Vec2 destination = Me::Math::Vec2(a_destination->m_tileX, a_destination->m_tileY);

    Me::Math::Vec2 dir = (destination - origin);

    dir.ABS();

    if(dir.m_x == dir.m_y)
    {
        //Diagonal
        if(pType == PawnTypes::Bishop || pType == PawnTypes::Queen)
        {
            return true;
        }
    }
    else if((dir.m_x == 0 && dir.m_y != 0 ) || (dir.m_x != 0 && dir.m_y == 0 ))
    {
        //Horizonal and Vertical
        if(pType == PawnTypes::Rook || pType == PawnTypes::Queen)
        {
            return true;
        }
    }
    else if(pType == PawnTypes::Knight)
    {
        if((dir.m_x == 2 && dir.m_y == 1) || (dir.m_x == 1 && dir.m_y == 2))
        {
            return true;
        }
    }

    return false;
}