#include "PCH.h"

#include "Games/Chess/ChessGame.h"
#include "Games/Chess/ChessHelper.h"

#include "MeduzaIncluder.h"

#include "Components/Chess/ChessBoardComponent.h"
#include "Components/Chess/ChessPawnComponent.h"
#include "Components/Chess/ChessAIComponent.h"
#include "Components/Chess/ChessPlayerComponent.h"

#include "Systems/Chess/ChessPawnSystem.h"
#include "Systems/Chess/ChessPlayerSystem.h"
#include "Systems/Chess/ChessAISystem.h"


Chess::ChessGame::ChessGame()
{
   m_gameName = "Chess"; 

   new Chess::ChessPawnSystem();
   new Chess::ChessAISystem();
   new Chess::ChessPlayerSystem();
}

Chess::ChessGame::~ChessGame()
{
    
}

void Chess::ChessGame::InitGame()
{
   Me::EntityManager* eManager = Me::EntityManager::GetEntityManager();

   auto cC = new Me::CameraComponent();
   cC->m_cameraType = Me::CameraType::Orthographic;
   cC->m_near = 0.0f;
   cC->m_far = 100;
   cC->m_size = Me::Event::EventSystem::GetEventSystem()->ScreenSize();

   EntityID entCam = Me::EntityManager::CreateEntity();
   eManager->AddComponent<Me::CameraComponent>(entCam, cC);
   eManager->AddComponent<Me::TransformComponent>(entCam);

   auto board = CreateBoard();
   if(board == nullptr)
   {
      ME_GAME_ASSERT_M(false, "Failed to create Chess Board!")
   }

//Create Player
   EntityID player = eManager->CreateEntity();
   ChessPlayerComponent* pComp = new ChessPlayerComponent();
   pComp->m_board = board;
   pComp->m_playerColour = Colour::White;
   eManager->AddComponent<ChessPlayerComponent>(player, pComp);
//Create AI
   EntityID ai = eManager->CreateEntity();
   ChessAIComponent* aiComp = new ChessAIComponent();
   aiComp->m_board = board;
   aiComp->m_aiColour = Colour::Black;
   eManager->AddComponent<ChessAIComponent>(ai, aiComp);

   switch (board->m_activePlayer)
   {
   case Colour::White:
         ME_GAME_LOG("White Player starts!");
      break;
   case Colour::Black:
         ME_GAME_LOG("Black Player starts!");
      break;
   }
}

Chess::ChessBoardComponent* Chess::ChessGame::CreateBoard()
{
   Me::EntityManager* eManager = Me::EntityManager::GetEntityManager();

   EntityID boardEntt = eManager->CreateEntity();
   ChessBoardComponent* boardComp = new ChessBoardComponent();
   boardComp->m_activePlayer = Colour::White;
   eManager->AddComponent<ChessBoardComponent>(boardEntt, boardComp);


   Me::Shader mesh = Me::Resources::MeshLibrary::GetMeshIndex(Me::Primitives::Quad);
   Me::Shader shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/UnlitColour_Shader.hlsl");
   
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

         Me::Math::Vec3 position;

         position.m_x = static_cast<float>(x * gs_tileSize);
         position.m_y = static_cast<float>(y * gs_tileSize);
         position.m_z = 2;
         tComp->m_translation = position;
         tComp->m_scale = Me::Math::Vec3(gs_tileSize);

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

   return boardComp;
}

void Chess::ChessGame::CreatePieces(ChessBoardComponent* a_board)
{
   if(a_board == nullptr)
   {
      ME_GAME_ASSERT_M(false, "ChessBoard is NullPtr!")
   }
   Me::EntityManager* eManager = Me::EntityManager::GetEntityManager();

   Me::Shader mesh = Me::Resources::MeshLibrary::GetMeshIndex(Me::Primitives::Quad);
   Me::Shader shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/Unlit_Shader.hlsl");
   Me::Texture texture = Me::Resources::TextureLibrary::CreateTexture("Assets/Textures/ChessPieces.png");
   
   if(shader == 0)
   {      
		shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/Unlit_Shader.glsl");
   }

   Me::Colour colour = Me::Colours::WHITE;
   Colour pawnColour = Colour::White;

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

            pawnComp->m_pawnColour = pawnColour;
            pawnComp->m_pawnType = Pawns::Pawn;
            pawnComp->m_boardPos = Me::Math::Vec2(x,y);
            pawnComp->m_pawnEntity = pawn;

            Me::Math::Vec3 position = tComp->m_translation;

            position.m_x = static_cast<float>(x * gs_tileSize);
            position.m_y = static_cast<float>(y * gs_tileSize);

            tComp->m_translation = position;
            tComp->m_scale = Me::Math::Vec3(gs_tileSize);
            
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
            
            pawnComp->m_pawnColour = pawnColour;
            pawnComp->m_boardPos = Me::Math::Vec2(x,y);
            pawnComp->m_pawnEntity = pawn;
            
            Me::Math::Vec3 position = tComp->m_translation;

            position.m_x = static_cast<float>(x * gs_tileSize);
            position.m_y = static_cast<float>(y * gs_tileSize);

            tComp->m_translation = position;
            tComp->m_scale = Me::Math::Vec3(gs_tileSize);
            
            rComp->m_shader = shader;
            rComp->m_texture = texture;
            rComp->m_mesh = mesh;             
            rComp->m_colour = colour;

            if(x == 0 || x == 7)//Rook
            {
               rComp->m_textureCoords = Me::Utils::TextureSlice(  Me::Math::Vec2(1024,170),
                                                Me::Math::Vec2(680,0),
                                                Me::Math::Vec2(170,170));
               pawnComp->m_pawnType = Pawns::Rook;
            } 
            else if(x == 1 || x == 6)//Knight
            {
               rComp->m_textureCoords = Me::Utils::TextureSlice(  Me::Math::Vec2(1024,170),
                                                Me::Math::Vec2(510,0),
                                                Me::Math::Vec2(170,170));
               pawnComp->m_pawnType = Pawns::Knight;
            }
            else if(x == 2 || x == 5)//Bishop
            {
               rComp->m_textureCoords = Me::Utils::TextureSlice(  Me::Math::Vec2(1024,170),
                                                Me::Math::Vec2(340,0),
                                                Me::Math::Vec2(170,170));
            pawnComp->m_pawnType = Pawns::Bishop;
            }
            else if(x == 3)//Queen
            {
               rComp->m_textureCoords = Me::Utils::TextureSlice(  Me::Math::Vec2(1024,170),
                                                Me::Math::Vec2(170,0),
                                                Me::Math::Vec2(170,170));
               pawnComp->m_pawnType = Pawns::Queen;
            }
            else if(x == 4)//King
            {
               rComp->m_textureCoords = Me::Utils::TextureSlice(  Me::Math::Vec2(1024,170),
                                                Me::Math::Vec2(0,0),
                                                Me::Math::Vec2(170,170));
               pawnComp->m_pawnType = Pawns::King;
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
         pawnColour = Colour::Black;
      }
   }

}