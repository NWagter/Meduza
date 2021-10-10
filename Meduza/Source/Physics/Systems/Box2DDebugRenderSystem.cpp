#include "MePCH.h"
#include "Physics/Systems/Box2DDebugRenderSystem.h"

#include "ECS/EntityManager.h"

#include "Platform/General/Graphics/RenderLayer.h"

#include "Core/Components/RenderComponent.h"
#include "Core/Components/TransformComponent.h"

#include "Physics/Physics.h"
#include "Physics/Components/BoxCollider2DComponent.h"

#include "Platform/General/ShaderLibrary.h"
#include "Platform/General/MeshLibrary.h"

#include "Platform/General/Resources/Mesh.h"

#include "Core/Meduza.h"

Me::Box2DDebugRenderSystem::Box2DDebugRenderSystem(Renderer::RenderLayer* a_renderLayer)
{ 
    m_renderLayer = a_renderLayer;
    m_executeMask = EXECUTE_INEDITOR;

    m_debugColour = Colours::MAGENTA;
    m_debugColour.m_colour[3] = 0.4f;

    m_debugMesh = Resources::MeshLibrary::GetMeshIndex(Primitives::Quad);

    m_debugShader = Resources::ShaderLibrary::CreateShader("Assets/Shaders/UnlitColour_Shader.glsl");

}

void Me::Box2DDebugRenderSystem::OnUpdate(float)
{
    if(Meduza::GetDebugState() & DEBUG_OFF)
    {
        return;
    }

    for(auto& compTuple : m_components)
    {
        TransformComponent* tC = std::get<TransformComponent*>(compTuple);
        Physics::BoxCollider2DComponent* bC = std::get<Physics::BoxCollider2DComponent*>(compTuple);
        DebugRenderComponent* dR = std::get<DebugRenderComponent*>(compTuple);
        

        if(!dR->m_dirtyFlag)
        {
            dR->m_mesh = m_debugMesh;
            dR->m_shader = m_debugShader;
            dR->m_debugColour = m_debugColour;
            dR->m_dirtyFlag = true;
        }

        TransformComponent trans = *tC;

        trans.m_translation.m_x += bC->m_colliderOffset.m_x;
        trans.m_translation.m_y += bC->m_colliderOffset.m_y;
        trans.m_scale.m_x = bC->m_colliderSize.m_x;
        trans.m_scale.m_y = bC->m_colliderSize.m_y;

        m_renderLayer->DebugSubmit(*dR, trans);
    }
}