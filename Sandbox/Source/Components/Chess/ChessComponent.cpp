#include "PCH.h"
#include "Components/GameComponents.h"

#include "Components/Chess/ChessBoardComponent.h"
#include "Components/Chess/ChessPawnComponent.h"
#include "Components/Chess/ChessAIComponent.h"
#include "Components/Chess/ChessPlayerComponent.h"

namespace Chess
{

    ComponentID ChessBoardComponent::s_componentID = static_cast<ComponentID>(GameComponents::ChessBoardComponent);
    ComponentID ChessPawnComponent::s_componentID = static_cast<ComponentID>(GameComponents::ChessPawnComponent);
    ComponentID ChessAIComponent::s_componentID = static_cast<ComponentID>(GameComponents::ChessAIComponent);
    ComponentID ChessPlayerComponent::s_componentID = static_cast<ComponentID>(GameComponents::ChessPlayerComponent);
    
}
