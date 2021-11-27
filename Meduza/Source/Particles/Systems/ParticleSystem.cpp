#include "MePCH.h"

#include "Particles/Systems/ParticleSystem.h"

#include "Core/Components/TransformComponent.h"
#include "Particles/Components/ParticleComponent.h"
#include "Particles/Components/ParticleSystemComponent.h"

Me::Particle::ParticleSystem::ParticleSystem()
{

}

void Me::Particle::ParticleSystem::OnUpdate(float a_dt)
{
    auto eManager = EntityManager::GetEntityManager();


    for (int i = 0; i < m_entities.size();  i++)
    {
        Me::TransformComponent* trans = std::get<Me::TransformComponent*>(m_components[i]);
        Me::Particle::ParticleComponent* particleComponent = std::get<Me::Particle::ParticleComponent*>(m_components[i]);

        trans->m_translation += (particleComponent->m_direction * particleComponent->m_speed) * a_dt;
        particleComponent->m_lifeTime -= a_dt;

        if (particleComponent->m_lifeTime <= 0)
        {
            particleComponent->m_parent->m_currentParticles--;
            eManager->DestroyEntity(m_entities[i]);
        }
    }
}