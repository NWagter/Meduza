#include "MePCH.h"
#include "AI/Systems/AgentMovementSystem.h"

#include "Core/Components/TransformComponent.h"
#include "AI/Components/AgentComponent.h"

Me::AI::AgentMovementSystem::AgentMovementSystem()
{

}

Me::AI::AgentMovementSystem::~AgentMovementSystem()
{
    
}

void Me::AI::AgentMovementSystem::OnUpdate(float a_dt)
{

    for(int i = 0; i < m_entities.size(); i++)
    {
        auto tC = std::get<TransformComponent*>(m_components[i]);
        auto aC = std::get<AgentComponent*>(m_components[i]);

        if(Math::Distance(tC->m_translation, aC->m_targetLocation) < aC->m_stopDistance)
        {
            continue;
        }
        
        // Navigation should happen here to determine the direction to travel and apply this to the translation

        tC->m_translation = Math::MoveTowards(tC->m_translation, aC->m_targetLocation,  aC->m_agentSpeed * a_dt);
    }
}