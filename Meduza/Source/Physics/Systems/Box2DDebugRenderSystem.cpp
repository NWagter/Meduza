#include "MePCH.h"
#include "Physics/Systems/Box2DDebugRenderSystem.h"

#include "Utils/MeduzaDebug.h"

#include "ECS/EntityManager.h"

#include "Platform/General/Graphics/RenderLayer.h"

#include "Core/Components/RenderComponent.h"
#include "Core/Components/TransformComponent.h"

#include "Physics/Physics.h"
#include "Physics/Components/BoxCollider2DComponent.h"

#include "Platform/General/Resources/Shader.h"
#include "Platform/General/ResourceLibrary.h"

#include "Core/Meduza.h"

Me::Box2DDebugRenderSystem::Box2DDebugRenderSystem(Renderer::RenderLayer* a_renderLayer)
{ 
    m_renderLayer = a_renderLayer;
    m_executeMask = EXECUTE_ALL;

    m_debugColour = Colours::MAGENTA;
    m_debugColour.m_colour[3] = 0.4f;

    m_debugMesh = static_cast<Resource>(Primitives::Quad);

    m_debugShader = Resources::ResourceLibrary::GetInstance()->LoadResource<Resources::ShaderBase>("Resources/Shaders/UnlitColour_Shader.glsl")->GetID();

}

void Me::Box2DDebugRenderSystem::OnUpdate(float)
{    
    if(!Debug::MeduzaDebug::GetDebuggingSettings().m_collisionDebugger)
    {
        return;
    }
    
    ME_PROFILE_FUNC("Box2DDebugRenderSystem");

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