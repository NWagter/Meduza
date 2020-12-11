#pragma once

#include "ECS/BaseComponent.h"
#include "ECS/EntityTypes.h"

#include "Core/MeduzaCore.h"

namespace Me
{
    
    struct RenderComponent : BaseComponent
    { 
        Colour m_colour;
        Mesh m_mesh;
        Shader m_shader;
        Texture m_texture;

        Math::Vec4 m_textureCoords = Math::Vec4(0,0,1,1);

        static ComponentID s_componentID;
    };
}