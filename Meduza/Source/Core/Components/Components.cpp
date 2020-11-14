#include "MePCH.h"

#include "Core/Components/CameraComponent.h"
#include "Core/Components/TransformComponent.h"
#include "Core/Components/RenderComponent.h"


ComponentID Me::TransformComponent::s_componentID = static_cast<ComponentID>(Components::Transform);
ComponentID Me::RenderComponent::s_componentID = static_cast<ComponentID>(Components::Render);
ComponentID Me::CameraComponent::s_componentID = static_cast<ComponentID>(Components::Camera);