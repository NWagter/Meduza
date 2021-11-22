#pragma once

#include "ECS/BaseComponent.h"

namespace Me
{
    namespace Particle
    {
        struct ParticleSystemComponent;

        struct ParticleComponent : public BaseComponent
        {
            Math::Vec3 m_velocity;
            float m_lifeTime;            

            ParticleSystemComponent* m_parent;

            static ComponentID s_componentID;
        };

    }
}