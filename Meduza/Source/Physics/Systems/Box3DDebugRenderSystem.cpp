#include "MePCH.h"
#include "Physics/Systems/Box3DDebugRenderSystem.h"

#include "ECS/EntityManager.h"

#include "Platform/General/Graphics/RenderLayer.h"

#include "Core/Components/RenderComponent.h"
#include "Core/Components/TransformComponent.h"

#include "Physics/Physics.h"
#include "Physics/Components/BoxCollider3DComponent.h"

#include "Platform/General/ShaderLibrary.h"
#include "Platform/General/MeshLibrary.h"

#include "Platform/General/Resources/Mesh.h"

#include "Core/Meduza.h"

Me::Box3DDebugRenderSystem::Box3DDebugRenderSystem(Renderer::RenderLayer* a_renderLayer)
{ 
    m_renderLayer = a_renderLayer;
    m_executeMask = EXECUTE_ALL;

    m_debugColour = Colours::MAGENTA;
    m_debugColour.m_colour[3] = 0.4f;

    m_debugMesh = Resources::MeshLibrary::GetMeshIndex(Primitives::Cube);

    m_debugShader = Resources::ShaderLibrary::CreateShader("Assets/Shaders/UnlitColour_Shader.glsl");

}

void Me::Box3DDebugRenderSystem::OnUpdate(float)
{
    if(Meduza::GetDebugState() & DEBUG_OFF)
    {
        return;
    }

    for(auto& compTuple : m_components)
    {
        TransformComponent* tC = std::get<TransformComponent*>(compTuple);
        Physics::BoxCollider3DComponent* bC = std::get<Physics::BoxCollider3DComponent*>(compTuple);
        DebugRenderComponent* dR = std::get<DebugRenderComponent*>(compTuple);
        

        if(!dR->m_dirtyFlag)
        {
            dR->m_mesh = m_debugMesh;
            dR->m_shader = m_debugShader;
            dR->m_debugColour = m_debugColour;
            dR->m_dirtyFlag = true;
        }

        TransformComponent trans = *tC;

        trans.m_translation += bC->m_colliderOffset;
        trans.m_scale = bC->m_colliderSize;

        m_renderLayer->DebugSubmit(*dR, trans);
    }
}