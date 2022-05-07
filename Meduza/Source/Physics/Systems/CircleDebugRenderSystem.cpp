#include "MePCH.h"
#include "Physics/Systems/CircleDebugRenderSystem.h"

#include "Utils/MeduzaDebug.h"

#include "ECS/EntityManager.h"

#include "Platform/General/Graphics/RenderLayer.h"

#include "Core/Components/RenderComponent.h"
#include "Core/Components/TransformComponent.h"

#include "Physics/Physics.h"
#include "Physics/Components/CircleColliderComponent.h"

#include "Core/Meduza.h"

Me::CircleDebugRenderSystem::CircleDebugRenderSystem()
{
    m_executeMask = EXECUTE_ALL;

    m_debugColour = Colours::MAGENTA;
    m_debugColour.m_colour[3] = 0.4f;

}

void Me::CircleDebugRenderSystem::OnUpdate(float)
{
    Debug::Settings settings = Debug::MeduzaDebug::GetDebuggingSettings();
    if (!settings.m_collisionDebugger || !settings.m_debugCircle)
    {
        return;
    }

    ME_PROFILE_FUNC("CircleDebugRenderSystem");

    for (auto& compTuple : m_components)
    {
        TransformComponent* tC = std::get<TransformComponent*>(compTuple);
        Physics::CircleColliderComponent* cC = std::get<Physics::CircleColliderComponent*>(compTuple);

        Math::Vector3 translation = tC->m_translation;

        translation += cC->m_colliderOffset;
        
        Math::Matrix4 trans = Math::Matrix4::Identity();
        trans.SetPosition(translation);

        Debug::MeduzaDebug::RenderCircle(trans, cC->m_radius, m_debugColour);
    }
}