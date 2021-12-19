#include "MePCH.h"

#include "Particles/Systems/ParticleEmitterSystem.h"

#include "Core/Components/TransformComponent.h"
#include "Core/Components/RenderComponent.h"

#include "Particles/Components/ParticleSystemComponent.h"
#include "Particles/Components/ParticleComponent.h"

#include "Platform/General/Resources/Shader.h"
#include "Platform/General/ResourceLibrary.h"

Me::Particle::ParticleEmitterSystem::ParticleEmitterSystem()
{
    m_defaultMesh = static_cast<Resource>(Primitives::Quad);
    m_defaultShader = Resources::ResourceLibrary::GetInstance()->LoadResource<Resources::ShaderBase>("Resources/Shaders/UnlitColour_Shader.glsl")->GetID();
}

void Me::Particle::ParticleEmitterSystem::OnUpdate(float a_dt)
{
    auto eManager = EntityManager::GetEntityManager();

    for (auto& compTuple : m_components)
    {
        Me::TransformComponent* trans = std::get<Me::TransformComponent*>(compTuple);
        Me::Particle::ParticleSystemComponent *particleSystem = std::get<Me::Particle::ParticleSystemComponent*>(compTuple);

        particleSystem->m_time += a_dt;

        if (particleSystem->m_currentParticles >= particleSystem->m_maxParticles)
        {
            continue;
        }


        if (particleSystem->m_time >= particleSystem->m_spawnRate)
        {
            //SpawnParticle
            EntityID ent = eManager->CreateEntity();

            particleSystem->m_currentParticles++;
            ParticleComponent* pComp = new ParticleComponent();
            Particle particle = particleSystem->m_particle;
            Math::Vec3 dir = particle.m_direction;

            if (particle.m_randomDirection)
            {
                dir = Math::RandomRange(dir, particle.m_directionRange);
            }


            pComp->m_direction = dir.Normalize();
            pComp->m_speed = particle.m_speed;
            pComp->m_lifeTime = particle.m_initialLifeTime;
            pComp->m_parent = particleSystem;


            TransformComponent* tComp = new TransformComponent();
            tComp->m_translation = trans->m_translation;

            RenderComponent* rComp = new RenderComponent();
            if (particleSystem->m_mesh != 0)
            {
                rComp->m_mesh = particleSystem->m_mesh;
            }
            else
            {
                rComp->m_mesh = m_defaultMesh;
            }            
            if (particleSystem->m_shader != 0)
            {
                rComp->m_shader = particleSystem->m_shader;
            }
            else
            {
                rComp->m_shader = m_defaultShader;
            }

            rComp->m_colour = particleSystem->m_particle.m_initalColour;

            eManager->AddComponent(ent, pComp);
            eManager->AddComponent(ent, tComp);
            eManager->AddComponent(ent, rComp);

            particleSystem->m_time = 0;
        }
    }
}