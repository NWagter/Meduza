#pragma once

#include "ECS/BaseComponent.h"

namespace Me
{    
    struct RenderComponent : BaseComponent
    { 
        Colour m_colour;
        Math::Vec4 m_textureCoords = Math::Vec4(0,0,1,1);

        static ComponentID s_componentID;

        Mesh m_mesh;
        Shader m_shader;
        Texture m_texture;

        std::string EditorComponentName() override { return "RenderComponent"; }
    };

    struct DebugRenderComponent : BaseComponent
    { 
        Colour m_debugColour;        
        static ComponentID s_componentID;

        Shader m_shader;
        Mesh m_mesh;

        bool m_dirtyFlag = false;
    };
}