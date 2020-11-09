#pragma once

#include "ECS/BaseComponent.h"
#include "ECS/EntityTypes.h"

namespace Me
{
    struct TransformComponent : public BaseComponent
    {
        static const ComponentID m_componentID = static_cast<ComponentID>(Components::Transform);

        ComponentID GetComponentID() override
        {
            return TransformComponent::m_componentID;
        }
    };
}