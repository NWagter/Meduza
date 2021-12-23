#pragma once
#include "Platform/General/Resources/MeshBase.h"

namespace Me
{
    namespace Resources
    {
        namespace GL
        {
            class Mesh : public MeshBase
            {
            public:
                Mesh(std::vector<Vertex> const& a_vertices, std::vector<uint16_t> const& a_indices);
                virtual ~Mesh();

                void SetMode(GLenum a_mode);
                void GenerateBuffers();
                void GenerateAttributes();

                unsigned int GetVBO() const { return m_vbo; }
                unsigned int GetVAO() const { return m_vao; }
                unsigned int GetIBO() const { return m_ibo; }

            private:
                unsigned int m_vbo;
                unsigned int m_ibo;
                unsigned int m_vao;

		        GLenum m_mode;
            };
        }
    }
}