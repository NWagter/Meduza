#include "PCH.h"
#include "Components/GameComponents.h"
#include "Components/CursorComponent.h"
#include "Components/PlayerComponent.h"
#include "Components/RotateComponent.h"
#include "Components/UpComponent.h"
#include "Components/ForwardComponent.h"


ComponentID CursorComponent::s_componentID = static_cast<ComponentID>(GameComponents::CursorComponent);
ComponentID PlayerComponent::s_componentID = static_cast<ComponentID>(GameComponents::PlayerComponent);
ComponentID RotateComponent::s_componentID = static_cast<ComponentID>(GameComponents::RotateComponent);
ComponentID UpComponent::s_componentID = static_cast<ComponentID>(GameComponents::UpComponent);
ComponentID ForwardComponent::s_componentID = static_cast<ComponentID>(GameComponents::ForwardComponent);


