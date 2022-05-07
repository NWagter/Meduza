#pragma once

#include "ECS/BaseComponent.h"

namespace Me
{
    namespace Particle
    {
        struct ParticleSystemComponent;

        struct ParticleComponent : public BaseComponent
        {
            Math::Vector3 m_direction;
            float m_speed;
            float m_lifeTime;            

            ParticleSystemComponent* m_parent;

            static ComponentID s_componentID;
        };

    }
}