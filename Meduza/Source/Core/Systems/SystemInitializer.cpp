#include "MePCH.h"
#include "Core/Systems/SystemInitializer.h"

#include "Platform/General/Graphics/RenderLayer.h"


#include "Core/Components/Components.h"

#include "Core/Systems/RenderSystem.h"
#include "Core/Systems/CameraSystem.h"
#include "Core/Systems/EditorCameraSystem.h"
#include "Core/Systems/MousePickingSystem.h"

#include "Core/Scripting/ScriptSystem.h"

#include "Physics/Systems/PhysicsSystem.h"
#include "Physics/Systems/GravitySystem.h"
#include "Physics/Systems/FluidDragSystem.h"

#include "Physics/Systems/CollisionSystem.h"
#include "Physics/Systems/Box2DDebugRenderSystem.h"
#include "Physics/Systems/Box3DDebugRenderSystem.h"
#include "Physics/Systems/SphereDebugRenderSystem.h"

#include "AI/Systems/AgentMovementSystem.h"
#include "AI/Systems/NavSurfaceSystem.h"



Me::SystemInitializer::SystemInitializer(Me::Renderer::RenderLayer& a_renderLayer)
{
	m_systems.push_back(new RenderSystem(&a_renderLayer));
	m_systems.push_back(new Box2DDebugRenderSystem(&a_renderLayer));
	m_systems.push_back(new Box3DDebugRenderSystem(&a_renderLayer));
	m_systems.push_back(new SphereDebugRenderSystem(&a_renderLayer));
	m_systems.push_back(new CameraSystem(&a_renderLayer));
    
	m_systems.push_back(new MousePickingSystem());
	m_systems.push_back(new Scripting::ScriptSystem());
	m_systems.push_back(new Editor::EditorCameraSystem());
	m_systems.push_back(new AI::AgentMovementSystem());
	m_systems.push_back(new AI::NavSurfaceSystem());

	m_systems.push_back(new Physics::PhysicsSystem()); //Clears and set Body correct
    m_systems.push_back(new Physics::CollisionSystem());
	m_systems.push_back(new Physics::FluidDragSystem()); //Check for drag behaviour
    m_systems.push_back(new Physics::GravitySystem()); //Check if gravity pushes through object after collision	
}

Me::SystemInitializer::~SystemInitializer()
{
    for(auto s : m_systems)
    {
        if(s != nullptr)
        {
            delete s;
        }
    }
}

void Me::SystemInitializer::PrintComponentsSize()
{
	int size = 0;
	size = sizeof(TagComponent);
	ME_LOG("Tag = %i \n", size);
	size = sizeof(EditorComponent);
	ME_LOG("EditorComponent = %i \n", size);
	size = sizeof(TransformComponent);
	ME_LOG("TransformComponent = %i \n", size);
	size = sizeof(RenderComponent);
	ME_LOG("RenderComponent = %i \n", size);
	size = sizeof(DebugRenderComponent);
	ME_LOG("DebugRenderComponent = %i \n", size);
	size = sizeof(CameraComponent);
	ME_LOG("CameraComponent = %i \n", size);
	size = sizeof(Physics::PhysicsComponent);
	ME_LOG("PhysicsComponent = %i \n", size);
	size = sizeof(Physics::ColliderComponent);
	ME_LOG("ColliderComponent = %i \n", size);
	size = sizeof(Physics::ColliderTagComponent);
	ME_LOG("ColliderTagComponent = %i \n", size);
	size = sizeof(Physics::BoxCollider2DComponent);
	ME_LOG("BoxCollider2DComponent = %i \n", size);
	size = sizeof(Physics::BoxCollider3DComponent);
	ME_LOG("BoxCollider3DComponent = %i \n", size);
	size = sizeof(Physics::SphereColliderComponent);
	ME_LOG("SphereColliderComponent = %i \n", size);
	size = sizeof(Me::AI::AgentComponent);
	ME_LOG("AgentComponent = %i \n", size);
	size = sizeof(Me::AI::NavSurfaceComponent);
	ME_LOG("NavSurfaceComponent = %i \n", size);
}