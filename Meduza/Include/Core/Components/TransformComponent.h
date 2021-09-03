#pragma once

#include "ECS/BaseComponent.h"
#include "ECS/EntityTypes.h"

namespace Me
{
    struct TransformComponent : public BaseComponent
    {
        private:
            Math::Mat4 m_transform = Math::Mat4::Identity();
            Math::Vec3 m_euler = Math::Vec3(0,0,0);
            Math::Vec3 m_scale = Math::Vec3(1,1,1);

        public:
            bool m_isStatic = false;

            //Getting
            Math::Mat4 GetTransform()
            {
                return m_transform;
            }

            Math::Vec3 GetPosition() 
            {
                return m_transform.GetPosition();
            }
            Math::Vec3 GetRotation() 
            {
                return m_euler;
            }
            Math::Vec3 GetScale() 
            { 
                return m_scale;
            }

            Math::Vec3 GetLeft()
            {
                Math::Vec3 right;
                
                right.m_x = m_transform.m_00;
                right.m_y = m_transform.m_01;
                right.m_z = m_transform.m_02;

                return right.Normalize();
            }    

            Math::Vec3 GetUp()
            {
                Math::Vec3 up;
                
                up.m_x = m_transform.m_10;
                up.m_y = m_transform.m_11;
                up.m_z = m_transform.m_12;

                return up.Normalize();
            }

            Math::Vec3 GetForward()
            {
                Math::Vec3 forward;
                
                forward.m_x = -m_transform.m_20;
                forward.m_y = -m_transform.m_21;
                forward.m_z = -m_transform.m_22;

                return forward.Normalize();
            }  

            //Setting
            Math::Vec3 SetPosition(Math::Vec3 a_pos)
            {
                if(m_isStatic)
                    return m_transform.GetPosition();

                m_transform.SetPosition(a_pos);

                return a_pos;
            }

            Math::Vec3 Translate(Math::Vec3 a_trans)
            {
                if(m_isStatic)
                    return m_transform.GetPosition();

                m_transform.Translate(a_trans);

                return m_transform.GetPosition();
            }
            Math::Vec3 SetRotationRadian(Math::Vec3 a_rot)
            {
                if(m_isStatic)
                    return GetRotation();
                    
                m_transform.Rotation(a_rot);
                m_euler = a_rot;
                return GetRotation();
            }
            Math::Vec3 SetRotationDegree(Math::Vec3 a_rot)
            {
                if(m_isStatic)
                    return GetRotation();
                    
                Math::Vec3 newRot;

                newRot.m_x = (Me::Math::gs_pi / 180) * a_rot.m_x;
                newRot.m_y = (Me::Math::gs_pi / 180) * a_rot.m_y;
                newRot.m_z = (Me::Math::gs_pi / 180) * a_rot.m_z;

                m_transform.Rotation(newRot);
                m_euler = newRot;
                return GetRotation();
            }
            Math::Vec3 SetUniformScale(float a_scale)
            {                
                if(m_isStatic)
                    return m_scale;

                m_scale = Math::Vec3(a_scale);

                return m_scale;
            }
            Math::Vec3 SetScale(Math::Vec3 a_scale)
            {                             
                if(m_isStatic)
                    return m_scale;

                m_scale = a_scale;

                return m_scale;                
            }
            
            static ComponentID s_componentID;
    };
}