#pragma once

namespace Me
{
    namespace Particle
    {
        struct Particle
        {
            Colour m_initalColour = Colour(1,0,1,1);
            Math::Vec3 m_velocity = Math::Vec3(-5, 10, 0);
            bool m_randomVelocity = true;
            Math::Vec3 m_velocityRange = Math::Vec3(5, 5, 0);

            float m_initialLifeTime = 5.0f;
        };

    }
}