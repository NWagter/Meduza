#include "PCH.h"
#include "Components/GameComponents.h"
#include "Components/CursorComponent.h"
#include "Components/MoveComponent.h"
#include "Components/TileComponent.h"
#include "Components/PlayerComponent.h"
#include "Components/PawnComponent.h"
#include "Components/ChessComponent.h"


ComponentID CursorComponent::s_componentID = static_cast<ComponentID>(GameComponents::CursorComponent);
ComponentID MoveComponent::s_componentID = static_cast<ComponentID>(GameComponents::MoveComponent);
ComponentID TileComponent::s_componentID = static_cast<ComponentID>(GameComponents::TileComponent);
ComponentID PlayerComponent::s_componentID = static_cast<ComponentID>(GameComponents::PlayerComponent);
ComponentID PawnComponent::s_componentID = static_cast<ComponentID>(GameComponents::PawnComponent);
ComponentID ChessComponent::s_componentID = static_cast<ComponentID>(GameComponents::ChessComponent);


