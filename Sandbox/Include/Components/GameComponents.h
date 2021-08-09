#pragma once

#include "ECS/EntityTypes.h"
#include "ECS/BaseComponent.h"
#include "MeduzaIncluder.h"

enum class GameComponents : uint16_t
{
    GameComponent = static_cast<uint16_t>(Components::Game),
    CursorComponent,
    PlayerComponent,
    RotateComponent,
    UpComponent,
    ForwardComponent,
    CameraControllerComponent,


//----------------------------------------------------------------       
// Chess
//----------------------------------------------------------------    
    ChessBoardComponent,
    ChessPawnComponent,
    ChessAIComponent,
    ChessPlayerComponent
    
};