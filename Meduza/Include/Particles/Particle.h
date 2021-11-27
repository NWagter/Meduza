#pragma once

namespace Me
{
    namespace Particle
    {
        struct Particle
        {
            Colour m_initalColour = Colour(1,0,1,1);
            Math::Vec3 m_direction = Math::Vec3(0, 1, 0);
            bool m_randomDirection = true;
            Math::Vec3 m_directionRange = Math::Vec3(-1, -1, 0);

            float m_initialLifeTime = 5.0f;
            float m_speed = 10;
        };

    }
}