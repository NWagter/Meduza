#pragma once

#include "ECS/BaseComponent.h"

#include "Physics/Physics.h"

namespace Me
{
    namespace Physics
    {
        struct ColliderComponent : public BaseComponent
        {            
            CollisionType m_collisionType;
            CollisionLayerID m_collisionLayer;

            virtual ComponentID GetColliderComponentID()
            {
                return s_componentID;
            }            

            static ComponentID s_componentID;
#ifdef PLATFORM_WINDOWS
#ifdef EDITOR
            void CustomGUI() override 
            {
                const char* collisionTypes[] = { "Overlap", "Block" };
                const char* currentCollisionType = collisionTypes[int(m_collisionType)];

                if (ImGui::BeginCombo("CollisionType", currentCollisionType))
                {
                    for (int i = 0; i < 2; i++)
                    {
                        bool isSelected = currentCollisionType == collisionTypes[i];

                        if (ImGui::Selectable(collisionTypes[i], isSelected))
                        {
                            currentCollisionType = collisionTypes[i];
                            m_collisionType = Physics::CollisionType(i);
                        }

                        if (isSelected)
                        {
                            ImGui::SetItemDefaultFocus();
                        }
                    }


                    ImGui::EndCombo();
                }
            }
#endif
#endif
        };

        struct ColliderTagComponent : public BaseComponent
        {            
            ColliderComponent* m_collider;

            static ComponentID s_componentID;

            ColliderTagComponent(ColliderComponent* a_collider)
            {
                m_collider = a_collider;
            }
        };
    }
}