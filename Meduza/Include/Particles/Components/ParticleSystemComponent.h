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
#ifdef PLATFORM_WINDOWS
#ifdef EDITOR
            void CustomGUI() override
            {
                ImGui::DragFloat("spawnRate", &m_spawnRate);
                ImGui::DragInt("maxParticles", &m_maxParticles);

                ImGui::DragFloat("Lifetime", &m_particle.m_initialLifeTime);
                ImGui::DragFloat("Speed", &m_particle.m_speed);
                ImGui::ColorEdit4("Colour", m_particle.m_initalColour.m_colour);
                Editor::Helper::EditorHelper::DrawVector3Prop("Direction", m_particle.m_direction);
                ImGui::Checkbox("RandomRange", &m_particle.m_randomDirection);
                if (m_particle.m_randomDirection)
                {
                    Editor::Helper::EditorHelper::DrawVector3Prop("DirectionRange", m_particle.m_directionRange);
                }
            }
#endif
#endif
            virtual bool RenderCustomGUI() { return true; }
            std::string EditorComponentName() override { return "ParticleSystemComponent"; }
        };

    }
}