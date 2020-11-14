#pragma once

namespace Me
{      
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

    struct Colour
    {
        Colour()
        {
            m_colour[0] = 1;
            m_colour[1] = 0;
            m_colour[2] = 1;
            m_colour[3] = 1; 
        }
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

        Vertex(float a_x, float a_y, float a_z, float a_u, float a_v)
        {
            m_vertexPos.m_x = a_x;
            m_vertexPos.m_y = a_y;
            m_vertexPos.m_z = a_z;

            m_uvCoord.m_x = a_u;
            m_uvCoord.m_y = a_v;
        }

        Math::Vec3 m_vertexPos;
        Math::Vec2 m_uvCoord;
    };
}