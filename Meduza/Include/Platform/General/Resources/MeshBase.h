#pragma once
#include "Platform/General/Resources/Resource.h"

namespace Me
{
    namespace Resources
    {
        class MeshBase : public ResourceBase
        {
        public:
            MeshBase();
            MeshBase(std::vector<Vertex> a_vertices, std::vector<uint16_t> a_indices);
            virtual ~MeshBase();   

            unsigned int GetVerticesSize() const
            {
                unsigned int size = static_cast<unsigned int>(m_vertices.size());

                return size;
            }
            inline unsigned int GetIndicesSize() const
            {
                unsigned int size = static_cast<uint16_t>(m_indices.size());

                return size;
            }

            inline std::vector<Vertex> GetVertices() const { return m_vertices; }
            inline std::vector<uint16_t> GetIndices() const { return m_indices; }

            MeshBase* OnCreate(const std::string& a_path) override;
            MeshBase* Create(std::vector<Vertex> a_vertices, std::vector<uint16_t> a_indices);
        protected:

            std::vector<Vertex> m_vertices;
            std::vector<uint16_t> m_indices;

            unsigned int m_vertexByteStride = 0;
            unsigned int m_vertexBufferByteSize = 0;
            unsigned int m_indexBufferByteSize = 0;
        };
    }
}