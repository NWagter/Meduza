#include "MePCH.h"
#include "Core/Systems/SystemInitializer.h"

#include "Platform/General/Graphics/RenderLayer.h"


#include "Core/Components/Components.h"

#include "Core/Systems/RenderSystem.h"
#include "Core/Systems/CameraSystem.h"
#ifdef EDITOR
#include "Core/Systems/EditorCameraSystem.h"
#endif
#include "Core/Systems/MousePickingSystem.h"

#include "Core/Scripting/ScriptSystem.h"

#include "Physics/Systems/PhysicsSystemBegin.h"
#include "Physics/Systems/PhysicsSystemEnd.h"
#include "Physics/Systems/ApplyForceSystem.h"
#include "Physics/Systems/GravitySystem.h"
#include "Physics/Systems/FluidDragSystem.h"
#include "Physics/Systems/FrictionSystem.h"
#include "Physics/Systems/BlockingSystem.h"

#include "Physics/Systems/CollisionSystem.h"
#ifdef EDITOR
#include "Physics/Systems/Box2DDebugRenderSystem.h"
#include "Physics/Systems/Box3DDebugRenderSystem.h"
#include "Physics/Systems/SphereDebugRenderSystem.h"
#endif

#include "AI/Systems/AgentMovementSystem.h"
#include "AI/Systems/NavSurfaceSystem.h"



Me::SystemInitializer::SystemInitializer(Me::Renderer::RenderLayer& a_renderLayer)
{
	m_systems.push_back(new RenderSystem(&a_renderLayer));
	m_systems.push_back(new Physics::PhysicsSystemBegin()); //Clears and set Body correct
	m_systems.push_back(new Physics::CollisionSystem());


#ifdef EDITOR
	m_systems.push_back(new Box2DDebugRenderSystem(&a_renderLayer));
	m_systems.push_back(new Box3DDebugRenderSystem(&a_renderLayer));
	m_systems.push_back(new SphereDebugRenderSystem(&a_renderLayer));
#endif
	m_systems.push_back(new CameraSystem(&a_renderLayer));
    
	m_systems.push_back(new MousePickingSystem());
	m_systems.push_back(new Scripting::ScriptSystem());

#ifdef EDITOR
	m_systems.push_back(new Editor::EditorCameraSystem());
#endif // EDITOR
	m_systems.push_back(new AI::AgentMovementSystem());
	m_systems.push_back(new AI::NavSurfaceSystem());

	m_systems.push_back(new Physics::GravitySystem());

	m_systems.push_back(new Physics::FluidDragSystem());
	m_systems.push_back(new Physics::FrictionSystem());

	//m_systems.push_back(new Physics::ApplyForceSystem());
	m_systems.push_back(new Physics::BlockingSystem());

	m_systems.push_back(new Physics::PhysicsSystemEnd()); //Clears and set Body correct
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