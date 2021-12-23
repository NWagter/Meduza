#pragma once

#include "ECS/BaseComponent.h"

namespace Me
{
    struct TransformComponent : public BaseComponent
    {
            Math::Vec3 m_translation = Math::Vec3(0,0,0);
            Math::Vec3 m_rotation = Math::Vec3(0,0,0); // Degree
            Math::Vec3 m_scale = Math::Vec3(1,1,1);

            static ComponentID s_componentID;

            bool m_isStatic = false;

            //Getting
            Math::Mat4 GetTransform() const
            {
                Math::Mat4 translationMat = Math::Mat4::Identity();
                translationMat.SetPosition(m_translation);
                
                // Degree to Radian
                Me::Math::Vec3 newRot;
                newRot.m_x = (Me::Math::gs_pi / 180) * m_rotation.m_x;
                newRot.m_y = (Me::Math::gs_pi / 180) * m_rotation.m_y;
                newRot.m_z = (Me::Math::gs_pi / 180) * m_rotation.m_z;

                Math::Mat4 rotationMat = Math::Mat4::Identity();
                rotationMat.Rotation(newRot);

                Math::Mat4 scaleMat = Math::Mat4::Identity();
                scaleMat.SetScale(m_scale);

                return translationMat * rotationMat * scaleMat;
            }
            
            void Reset() override
            {
                m_translation = Math::Vec3(0,0,0);
                m_rotation = Math::Vec3(0,0,0);
                m_scale = Math::Vec3(0,0,0);
            }

    };
}