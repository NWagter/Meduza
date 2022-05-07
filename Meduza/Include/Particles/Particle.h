#pragma once

namespace Me
{
    namespace Particle
    {
        struct Particle
        {
            Colour m_initalColour = Colour(1,0,1,1);
            Math::Vector3 m_direction = Math::Vector3(0, 1, 0);
            bool m_randomDirection = true;
            Math::Vector3 m_directionRange = Math::Vector3(-1, -1, 0);

            float m_initialLifeTime = 5.0f;
            float m_speed = 10;
        };

    }
}