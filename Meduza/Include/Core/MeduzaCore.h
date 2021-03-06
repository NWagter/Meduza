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

    enum class Primitives : uint16_t
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
        Vertex()
        {

        }

        Vertex(float a_x, float a_y, float a_z)
        {
            m_vertexPos = Math::Vec3(a_x,a_y,a_z);
        }

        Vertex(float a_x, float a_y, float a_z, float a_u, float a_v)
        {
            m_vertexPos = Math::Vec3(a_x,a_y,a_z);
            m_uvCoord = Math::Vec2(a_u, a_v);
        }
        
        Vertex(float a_x, float a_y, float a_z, float a_nX, float a_nY, float a_nZ)
        {
            m_vertexPos = Math::Vec3(a_x,a_y,a_z);
            m_normals = Math::Vec3(a_nX, a_nY,a_nZ);
        }  
        Vertex(float a_x, float a_y, float a_z, float a_nX, float a_nY, float a_nZ, float a_u, float a_v)
        {
            m_vertexPos = Math::Vec3(a_x,a_y,a_z);
            m_normals = Math::Vec3(a_nX, a_nY,a_nZ);
            m_uvCoord = Math::Vec2(a_u, a_v);
        }

        void SetNormals(float a_nX, float a_nY, float a_nZ)
        {
            m_normals = Math::Vec3(a_nX, a_nY,a_nZ);
        }
        void SetUV(float a_u, float a_v)
        {
            m_uvCoord = Math::Vec2(a_u, a_v);
        }

        Math::Vec3 m_vertexPos;
        Math::Vec3 m_normals;
        Math::Vec2 m_uvCoord;
    };
}