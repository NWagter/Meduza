#pragma once

#include "ECS/BaseComponent.h"
#include "Particles/Particle.h"

namespace Me
{
    namespace Particle
    {
        struct ParticleSystemComponent : public BaseComponent
        {
            Shader m_shader;
            Mesh m_mesh;

            int m_maxParticles = 1000;
            int m_currentParticles = 0;
            float m_spawnRate = 0.1f;

            float m_time = 0;

            Particle m_particle = Particle();

            static ComponentID s_componentID;
        };

    }
}