#pragma once

namespace Me
{        
    namespace Resources
    {
        class MeshBase;
        class ShaderBase;
        class TextureBase;
    }

    using Mesh = uint16_t;
    using Shader = uint16_t;
    using Texture = uint16_t;

    enum class ResourceTypes
    {
        Unknown_Type = 0,
        Mesh,
        Shader,
        Texture
    };

    enum class Primitives
    {
        Quad = 0,
        Cube,
        Plane,
        Sphere,
        Torus
    };

    struct Renderable
    {
        Mesh m_mesh;
        Shader m_shader;
    };

    struct Colour
    {
        Colour(float a_r, float a_g, float a_b, float a_a)
        {
            m_colour[0] = a_r;
            m_colour[1] = a_g;
            m_colour[2] = a_b;
            m_colour[3] = a_a;
        }

        Colour(float a_colour[4])
        {
            for(int i = 0; i < 4;i++)
            {
                m_colour[i] = a_colour[i];
            }
        }

        float m_colour[4];
    };
    
    struct Vertex
    {
        Vertex(float a_x, float a_y, float a_z)
        {
            m_vertexPos.m_x = a_x;
            m_vertexPos.m_y = a_y;
            m_vertexPos.m_z = a_z;
        }

        Math::Vec3 m_vertexPos;
    };
}