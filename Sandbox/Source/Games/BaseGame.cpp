#include "PCH.h"
#include "Games/BaseGame.h"

#include "MeduzaIncluder.h"

BaseGame::BaseGame()
{
    
}

void BaseGame::InitGame()
{
    Me::Serialization::Serializer::GetInstance()->DeserializeScene("Assets/Scenes/Megaman_Close.scene");
}

void BaseGame::UpdateGame(float)
{

}