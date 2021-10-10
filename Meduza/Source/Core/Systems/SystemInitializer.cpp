#include "MePCH.h"
#include "Core/Systems/SystemInitializer.h"

#include "Platform/General/Graphics/RenderLayer.h"


#include "Core/Components/Components.h"

#include "Core/Systems/RenderSystem.h"
#include "Core/Systems/CameraSystem.h"
#include "Core/Systems/EditorCameraSystem.h"
#include "Core/Systems/MousePickingSystem.h"

#include "Physics/Systems/PhysicsSystem.h"
#include "Physics/Systems/GravitySystem.h"
#include "Physics/Systems/CollisionSystem.h"
#include "Physics/Systems/Box2DDebugRenderSystem.h"
#include "Physics/Systems/Box3DDebugRenderSystem.h"

#include "AI/Systems/AgentMovementSystem.h"
#include "AI/Systems/NavSurfaceSystem.h"



Me::SystemInitializer::SystemInitializer(Me::Renderer::RenderLayer& a_renderLayer)
{
	
	m_systems.push_back(new RenderSystem(&a_renderLayer));
	m_systems.push_back(new Box2DDebugRenderSystem(&a_renderLayer));
	m_systems.push_back(new Box3DDebugRenderSystem(&a_renderLayer));
	m_systems.push_back(new CameraSystem(&a_renderLayer));
    
	m_systems.push_back(new MousePickingSystem());
	m_systems.push_back(new Editor::EditorCameraSystem());
	m_systems.push_back(new AI::AgentMovementSystem());
	m_systems.push_back(new AI::NavSurfaceSystem());

	m_systems.push_back(new Physics::PhysicsSystem()); //Clears and set Body correct
    m_systems.push_back(new Physics::CollisionSystem());
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