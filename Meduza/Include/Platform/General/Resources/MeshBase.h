#pragma once
namespace Me
{
    namespace Resources
    {
        class MeshBase
        {
        public:
            MeshBase(std::string, std::vector<Vertex>, std::vector<uint16_t>);
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

            inline std::string GetPath() const {return m_filePath;}
        protected:
            std::string m_filePath;
            std::vector<Vertex> m_vertices;
            std::vector<uint16_t> m_indices;

            unsigned int m_vertexByteStride = 0;
            unsigned int m_vertexBufferByteSize = 0;
            unsigned int m_indexBufferByteSize = 0;
        };
    }
}