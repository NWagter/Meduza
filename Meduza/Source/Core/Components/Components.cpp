#include "MePCH.h"

#include "Core/Components/CameraComponent.h"
#include "Core/Components/TransformComponent.h"
#include "Core/Components/RenderComponent.h"
#include "Core/Scripting/ScriptComponent.h"

#include "Physics/Components/PhysicsComponent.h"
#include "Physics/Components/BoxCollider2DComponent.h"
#include "Physics/Components/BoxCollider3DComponent.h"
#include "Physics/Components/SphereColliderComponent.h"

#include "AI/Components/AgentComponent.h"
#include "AI/Components/NavSurfaceComponent.h"


ComponentID Me::TagComponent::s_componentID = static_cast<ComponentID>(Components::Tag);
ComponentID Me::EditorComponent::s_componentID = static_cast<ComponentID>(Components::Editor);
ComponentID Me::TransformComponent::s_componentID = static_cast<ComponentID>(Components::Transform);
ComponentID Me::RenderComponent::s_componentID = static_cast<ComponentID>(Components::Render);
ComponentID Me::DebugRenderComponent::s_componentID = static_cast<ComponentID>(Components::DebugRender);
ComponentID Me::CameraComponent::s_componentID = static_cast<ComponentID>(Components::Camera);

ComponentID Me::Physics::PhysicsComponent::s_componentID = static_cast<ComponentID>(Components::Physics);
ComponentID Me::Physics::ColliderComponent::s_componentID = static_cast<ComponentID>(Components::Collider);
ComponentID Me::Physics::ColliderTagComponent::s_componentID = static_cast<ComponentID>(Components::ColliderTag);
ComponentID Me::Physics::BoxCollider2DComponent::s_componentID = static_cast<ComponentID>(Components::BoxCollider2D);
ComponentID Me::Physics::BoxCollider3DComponent::s_componentID = static_cast<ComponentID>(Components::BoxCollider3D);
//ComponentID Me::Physics::CircleColliderComponent::s_componentID = static_cast<ComponentID>(Components::CircleCollider);
ComponentID Me::Physics::SphereColliderComponent::s_componentID = static_cast<ComponentID>(Components::SphereCollider);
ComponentID Me::Scripting::ScriptComponent::s_componentID = static_cast<ComponentID>(Components::Scripting);

ComponentID Me::AI::AgentComponent::s_componentID = static_cast<ComponentID>(Components::AgentComponent);
ComponentID Me::AI::NavSurfaceComponent::s_componentID = static_cast<ComponentID>(Components::NavSurfaceComponent);