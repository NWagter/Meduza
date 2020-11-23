#include "PCH.h"
#include "Systems/ChessboardSystem.h"

#include "MeduzaIncluder.h"

#include "Components/ChessComponent.h"

#include "Components/TileComponent.h"
#include "Components/PawnComponent.h"

#include "Components/PlayerComponent.h"
#include "Components/CursorComponent.h"

static char chars[] =
{
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'
};

static constexpr float TILE_SIZE = 32;

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

    EntityID chessEnt = 0;
    for(auto entt : entList)
    {
        if(entt.second.find(ChessComponent::s_componentID) != entt.second.end())
        {            
            chessEnt = entt.first;
            break;
        }
    }

    m_chessEntity = chessEnt;
}

void ChessboardSystem::OnUpdate(float)
{    
    Me::Math::Vec2 pos;

    bool onClick = false;
    bool onLeftClick = false;
    PlayerComponent* player = nullptr;
    ChessComponent* chess = nullptr;

    if(m_chessEntity != 0)
    {    
        chess = Me::EntityManager::GetEntityManager()->GetComponent<ChessComponent>(m_chessEntity);
    }

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
        if(chess == nullptr)
        {
            ME_CORE_ASSERT_M(false, "We don't have a Chess system to controll the playing field!");
            break;
        }
        else
        {
            if(chess->m_movingPawn != nullptr)
            {
                break;
            }
        }


        if(onClick)
        {
            ChessBoardComponent* board = std::get<ChessBoardComponent*>(compTuple);

            int x = static_cast<int>(floorf((pos.m_x + (TILE_SIZE / 2)) / TILE_SIZE));
            int y = static_cast<int>(floorf((pos.m_y + (TILE_SIZE / 2)) / TILE_SIZE));
            TileComponent* tile = nullptr;

            if((x < 8 && x >= 0) && (y < 8 && y >= 0))
            {
                tile = GetTile(x,y, board);
            }

            if(tile != nullptr)
            {
                Me::Math::Vec3 tPos = Me::Math::Vec3(tile->m_tileX * TILE_SIZE, tile->m_tileY * TILE_SIZE, 9);

                if(player->m_selectedPawn != nullptr)
                {
                    auto selectedPawn = player->m_selectedPawn;
                    if(CheckMove(selectedPawn, tile, board))
                    {
                        
                        if(!selectedPawn->m_hasMoved)
                        {
                            //Required for Pawn
                            selectedPawn->m_hasMoved = true;
                        }
                        selectedPawn->m_newPos = tPos;
                        selectedPawn->m_moving = true;
                        selectedPawn->m_tile->m_pawn = nullptr;
                        selectedPawn->m_tile = tile;  
                        chess->m_movingPawn = selectedPawn;                      
                    }
                    
                    player->m_selectedPawn = nullptr;
                    break;
                }              
                else
                {
                    auto pawn = tile->m_pawn;
                    if(pawn != nullptr && !pawn->m_moving && pawn->m_colour == chess->m_turn)
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

TileComponent* ChessboardSystem::GetTile(Me::Math::Vec2 a_pos, ChessBoardComponent* a_board)
{
    int x = static_cast<int>(a_pos.m_x);
    int y = static_cast<int>(a_pos.m_y);

    return a_board->m_chessBoard[x][y];
}
TileComponent* ChessboardSystem::GetTile(int a_x, int a_y, ChessBoardComponent* a_board)
{
    return a_board->m_chessBoard[a_x][a_y];
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

bool ChessboardSystem::CheckMove(PawnComponent* a_pawn, TileComponent* a_destination, ChessBoardComponent* a_board)
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
    Me::Math::Vec2 dirAbs = dir;
    dir.Normalize();
    dirAbs.ABS();

    bool obstacle = false;
    if(a_pawn->m_type != PawnTypes::Knight)
    {
        obstacle = CheckTiles(origin, destination, a_board);
    }

    if(obstacle)
    {
        return false;
    }

    if(pType == PawnTypes::Pawn)
    {
        if(dirAbs.m_x == dirAbs.m_y  && a_destination->m_pawn != nullptr)
        {
            if(dir.m_y > 0 && a_pawn->m_colour == PawnColour::White)
            {
                return true;
            }else if(dir.m_y < 0 && a_pawn->m_colour == PawnColour::Black)
            {
                return true;
            }
        }
        else if(dirAbs.m_x == 0)
        {
            if((!a_pawn->m_hasMoved && dirAbs.m_y > 2) || (a_pawn->m_hasMoved && dirAbs.m_y > 1))
            {
                return false;
            }

            if(GetTile(a_pawn->m_tile->m_tileX, a_pawn->m_tile->m_tileY + dir.m_y, a_board)->m_pawn != nullptr)
            {
                return false;
            }

            if(dir.m_y > 0 && a_pawn->m_colour == PawnColour::White)
            {
                return true;
            }
            else if(dir.m_y < 0 && a_pawn->m_colour == PawnColour::Black)
            {
                return true;
            }
        }
    }
    if(pType == PawnTypes::Bishop || pType == PawnTypes::Queen)
    {
        //Diagonal
        if(dirAbs.m_x == dirAbs.m_y)
        {
            return true;
        }
    }
    if(pType == PawnTypes::Rook || pType == PawnTypes::Queen)
    {
        //Horizonal and Vertical
        if((dirAbs.m_x == 0 && dirAbs.m_y != 0 ))
        {   
            return true;
        }
        else if((dirAbs.m_x != 0 && dirAbs.m_y == 0 ))
        {
            return true;
        }
    }
    if(pType == PawnTypes::Knight)
    {
        if((dirAbs.m_x == 2 && dirAbs.m_y == 1) || (dirAbs.m_x == 1 && dirAbs.m_y == 2))
        {
            return true;
        }
    }
    if(pType == PawnTypes::King)
    {
        if(dirAbs.m_x <= 1 && dirAbs.m_y <= 1)        
        {
            return true;
        }
    }

    return false;
}

bool ChessboardSystem::CheckTiles(Me::Math::Vec2 a_origin, Me::Math::Vec2 a_dest, ChessBoardComponent* a_board)
{
    Me::Math::Vec2 dir = (a_dest - a_origin).Normalize();
    auto d = Me::Math::Vec2(roundf(dir.m_x), roundf(dir.m_y));
    Me::Math::Vec2 currentPos = a_origin + d;
    
    while(currentPos != a_dest)
    {
        auto tile = GetTile(currentPos, a_board);
        if(tile->m_pawn != nullptr && currentPos != a_dest)
        {
            return true;
        }
        currentPos += d;
    }

    return false;
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

    tC->m_position = Me::Math::Vec3((a_col * TILE_SIZE),(a_row * TILE_SIZE),  9);
    tC->m_uniformScale = TILE_SIZE;

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

void ChessboardSystem::CreateBoard()
{
    auto quad = Me::Resources::MeshLibrary::GetMeshIndex(Me::Primitives::Quad);
    auto shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/FlatColour_Shader.hlsl");
    auto eManager = Me::EntityManager::GetEntityManager();

    if(shader == 0)
    {
        Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/Default_Shader.glsl");
    }

    auto chessBoardEntt = Me::EntityManager::CreateEntity();
    ChessBoardComponent* comp = new ChessBoardComponent();
    bool black = true;
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            auto entt = Me::EntityManager::CreateEntity();
            auto tC = new Me::TransformComponent();
            auto rC = new Me::RenderComponent();
            auto tileC = new TileComponent();

            tC->m_position = Me::Math::Vec3(x * TILE_SIZE, y * TILE_SIZE , 10);
            tC->m_uniformScale = TILE_SIZE;
            
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

            comp->m_chessBoard[x][y] = tileC;
        }

        black = !black;
    }

    eManager->AddComponent<ChessBoardComponent>(chessBoardEntt, comp);

}