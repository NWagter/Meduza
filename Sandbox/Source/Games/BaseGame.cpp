#include "PCH.h"
#include "Games/BaseGame.h"

#include "MeduzaIncluder.h"

BaseGame::BaseGame()
{
    
}

void BaseGame::InitGame()
{
    Me::Serialization::Serializer::GetInstance()->DeserializeScene("Assets/Scenes/MonkeyHeadScene.xml");
}

void BaseGame::UpdateGame(float)
{

}