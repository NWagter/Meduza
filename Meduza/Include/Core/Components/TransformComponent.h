#pragma once

#include "ECS/BaseComponent.h"
#include "ECS/EntityTypes.h"

namespace Me
{
    struct TransformComponent : public BaseComponent
    {
        private:
            Math::Vec3 m_position = Math::Vec3(0,0,0);
            Math::Vec3 m_rotation = Math::Vec3(0,0,0);
            float m_uniformScale = 1;

        public:
            bool m_isStatic = false;

            Math::Vec3 GetPosition() {return m_position;}
            Math::Vec3 GetRotation() {return m_rotation;}
            float GetUniformedScale() { return m_uniformScale;}
            Math::Vec3 SetPosition(Math::Vec3 a_pos)
            {
                if(m_isStatic)
                    return m_position;

                m_position = a_pos;
                return a_pos;
            }

            Math::Vec3 SetRotationRadian(Math::Vec3 a_rot)
            {
                if(m_isStatic)
                    return m_rotation;
                    
                m_rotation = a_rot;
                return m_rotation;
            }

            Math::Vec3 SetRotationDegree(Math::Vec3 a_rot)
            {
                if(m_isStatic)
                    return m_rotation;
                    
                Math::Vec3 newRot;

                newRot.m_x = (Me::Math::gs_pi / 180) * a_rot.m_x;
                newRot.m_y = (Me::Math::gs_pi / 180) * a_rot.m_y;
                newRot.m_z = (Me::Math::gs_pi / 180) * a_rot.m_z;

                m_rotation = newRot;
                return m_rotation;
            }

            float SetUniformScale(float a_scale)
            {                
                if(m_isStatic)
                    return m_uniformScale;

                m_uniformScale = a_scale;

                return m_uniformScale;
            }
            
            static ComponentID s_componentID;
    };
}