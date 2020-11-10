#pragma once

#include "ECS/BaseComponent.h"
#include "ECS/EntityTypes.h"

#include "Core/MeduzaCore.h"

namespace Me
{
    
    struct RenderComponent : BaseComponent
    {
        Mesh m_mesh;
        Shader m_shader;
        Texture m_texture;    

        static ComponentID s_componentID;
    };
}