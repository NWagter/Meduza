#include "PCH.h"

#include "Games/Chess/ChessGame.h"
#include "Games/Chess/ChessHelper.h"

#include "MeduzaIncluder.h"

#include "Components/Chess/ChessBoardComponent.h"
#include "Components/Chess/ChessPawnComponent.h"


Chess::ChessGame::ChessGame()
{
   m_gameName = "Chess"; 
}

Chess::ChessGame::~ChessGame()
{
    
}

void Chess::ChessGame::InitGame()
{
   CreateBoard();
}

void Chess::ChessGame::CreateBoard()
{
   Me::EntityManager* eManager = Me::EntityManager::GetEntityManager();

   EntityID boardEntt = eManager->CreateEntity();
   ChessBoardComponent* boardComp = new ChessBoardComponent();
   eManager->AddComponent<ChessBoardComponent>(boardEntt, boardComp);


   Me::Shader mesh = Me::Resources::MeshLibrary::GetMeshIndex(Me::Primitives::Quad);
   Me::Shader shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/FlatColour_Shader.hlsl");
   
   if(shader == 0)
   {      
		shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/Default_Shader.glsl");
   }

   bool black = true;
   for(int x = 0; x < gs_boardWidth; x++)
   {
      for(int y = 0; y < gs_boardHeight; y++)
      {
         EntityID tile = eManager->CreateEntity();
         Me::RenderComponent* rComp = new Me::RenderComponent();
         Me::TransformComponent* tComp = new Me::TransformComponent();

         tComp->m_position.m_x = static_cast<float>(x * gs_tileSize);
         tComp->m_position.m_y = static_cast<float>(y * gs_tileSize);
         tComp->m_position.m_z = 2;
         tComp->m_uniformScale = static_cast<float>(gs_tileSize);

         rComp->m_mesh = mesh;
         rComp->m_shader = shader;
         if(black)
         {
            rComp->m_colour = Me::Colours::TAUBMANS_WINTER_OAK;
         }else
         {
            rComp->m_colour = Me::Colours::AZURE_WHITE;
         }
         black = !black;
         boardComp->m_board[x][y] = nullptr;
         
         eManager->AddComponent<Me::RenderComponent>(tile, rComp);
         eManager->AddComponent<Me::TransformComponent>(tile, tComp);
      }
      black = !black;
   }

   CreatePieces(boardComp);
}

void Chess::ChessGame::CreatePieces(ChessBoardComponent* a_board)
{
   if(a_board == nullptr)
   {
      ME_CORE_ASSERT_M(false, "ChessBoard is NullPtr!")
   }
   Me::EntityManager* eManager = Me::EntityManager::GetEntityManager();

   Me::Shader mesh = Me::Resources::MeshLibrary::GetMeshIndex(Me::Primitives::Quad);
   Me::Shader shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/Default_Shader.hlsl");
   Me::Texture texture = Me::Resources::TextureLibrary::CreateTexture("Assets/Textures/ChessPieces.png");
   
   if(shader == 0)
   {      
		shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/Default_Shader.glsl");
   }

   Me::Colour colour = Me::Colours::WHITE;

   //Spawn Pawns
   for(int y = 0; y < 8; y++)
   {
      for(int x = 0; x < 8; x++)
      {
         if(y == 1 || y ==  6)
         {         
            EntityID pawn = eManager->CreateEntity();
            Me::RenderComponent* rComp = new Me::RenderComponent();
            Me::TransformComponent* tComp = new Me::TransformComponent();
            ChessPawnComponent* pawnComp = new ChessPawnComponent();

            tComp->m_position.m_x = static_cast<float>(x * gs_tileSize);
            tComp->m_position.m_y = static_cast<float>(y * gs_tileSize);
            tComp->m_uniformScale = static_cast<float>(gs_tileSize);
            
            rComp->m_shader = shader;
            rComp->m_texture = texture;
            rComp->m_mesh = mesh;

            rComp->m_textureCoords = Me::Utils::TextureSlice(  Me::Math::Vec2(1024,170),
                                                Me::Math::Vec2(850,0),
                                                Me::Math::Vec2(170,170));
            rComp->m_colour = colour;

            a_board->m_board[x][y] = pawnComp;
            eManager->AddComponent<Me::RenderComponent>(pawn, rComp);
            eManager->AddComponent<Me::TransformComponent>(pawn, tComp);  
            eManager->AddComponent<ChessPawnComponent>(pawn, pawnComp);         

         }
      
         if(y == 0 || y == 7)
         {
            EntityID pawn = eManager->CreateEntity();
            Me::RenderComponent* rComp = new Me::RenderComponent();
            Me::TransformComponent* tComp = new Me::TransformComponent();
            ChessPawnComponent* pawnComp = new ChessPawnComponent();

            tComp->m_position.m_x = static_cast<float>(x * gs_tileSize);
            tComp->m_position.m_y = static_cast<float>(y * gs_tileSize);
            tComp->m_uniformScale = static_cast<float>(gs_tileSize);
            
            rComp->m_shader = shader;
            rComp->m_texture = texture;
            rComp->m_mesh = mesh;             
            rComp->m_colour = colour;

            if(x == 0 || x == 7)//Rook
            {
               rComp->m_textureCoords = Me::Utils::TextureSlice(  Me::Math::Vec2(1024,170),
                                                Me::Math::Vec2(680,0),
                                                Me::Math::Vec2(170,170));
            } 
            else if(x == 1 || x == 6)//Knight
            {
               rComp->m_textureCoords = Me::Utils::TextureSlice(  Me::Math::Vec2(1024,170),
                                                Me::Math::Vec2(510,0),
                                                Me::Math::Vec2(170,170));
            }
            else if(x == 2 || x == 5)//Bishop
            {
               rComp->m_textureCoords = Me::Utils::TextureSlice(  Me::Math::Vec2(1024,170),
                                                Me::Math::Vec2(340,0),
                                                Me::Math::Vec2(170,170));
            }
            else if(x == 3)//Queen
            {
               rComp->m_textureCoords = Me::Utils::TextureSlice(  Me::Math::Vec2(1024,170),
                                                Me::Math::Vec2(170,0),
                                                Me::Math::Vec2(170,170));
            }
            else if(x == 4)//King
            {
               rComp->m_textureCoords = Me::Utils::TextureSlice(  Me::Math::Vec2(1024,170),
                                                Me::Math::Vec2(0,0),
                                                Me::Math::Vec2(170,170));
            }

            a_board->m_board[x][y] = pawnComp;
            eManager->AddComponent<Me::RenderComponent>(pawn, rComp);
            eManager->AddComponent<Me::TransformComponent>(pawn, tComp);  
            eManager->AddComponent<ChessPawnComponent>(pawn, pawnComp);      
         }         
      }
      if(y > 2)
      {
         colour = Me::Colours::RESENE_DARK_OAK;
      }
   }

}