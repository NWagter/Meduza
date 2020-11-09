#pragma once

#include "ECS/BaseComponent.h"
#include "ECS/EntityTypes.h"

#include "Core/MeduzaCore.h"

namespace Me
{
    
    struct RenderComponent : BaseComponent
    {
        static const ComponentID m_componentID = static_cast<ComponentID>(Components::Render);

        ComponentID GetComponentID() override
        {
            return RenderComponent::m_componentID;
        }

        Mesh m_mesh;
        Shader m_shader;
        Texture m_texture;    
    };
}