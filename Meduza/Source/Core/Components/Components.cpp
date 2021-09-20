#include "MePCH.h"

#include "Core/Components/CameraComponent.h"
#include "Core/Components/TransformComponent.h"
#include "Core/Components/RenderComponent.h"
#include "Core/Scripting/ScriptComponent.h"

#include "Physics/Components/PhysicsComponent.h"

#include "AI/Components/AgentComponent.h"
#include "AI/Components/NavSurfaceComponent.h"


ComponentID Me::TagComponent::s_componentID = static_cast<ComponentID>(Components::Tag);
ComponentID Me::EditorComponent::s_componentID = static_cast<ComponentID>(Components::Editor);
ComponentID Me::TransformComponent::s_componentID = static_cast<ComponentID>(Components::Transform);
ComponentID Me::RenderComponent::s_componentID = static_cast<ComponentID>(Components::Render);
ComponentID Me::CameraComponent::s_componentID = static_cast<ComponentID>(Components::Camera);

ComponentID Me::Physics::PhysicsComponent::s_componentID = static_cast<ComponentID>(Components::Physics);
ComponentID Me::Scripting::ScriptComponent::s_componentID = static_cast<ComponentID>(Components::Scripting);

ComponentID Me::AI::AgentComponent::s_componentID = static_cast<ComponentID>(Components::AgentComponent);
ComponentID Me::AI::NavSurfaceComponent::s_componentID = static_cast<ComponentID>(Components::NavSurfaceComponent);