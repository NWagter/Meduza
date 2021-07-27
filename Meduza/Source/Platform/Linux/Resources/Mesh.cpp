#include "MePCH.h"
#include "Platform/Linux/Resources/Mesh.h"

Me::Resources::GL::Mesh::Mesh(std::vector<Vertex> a_vertices, std::vector<uint16_t> a_indices)
 : MeshBase(a_vertices, a_indices)
{
    GenerateBuffers();
}

Me::Resources::GL::Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
}

void Me::Resources::GL::Mesh::SetMode(GLenum a_mode)
{
    m_mode = a_mode;
    glPolygonMode(GL_FRONT_AND_BACK, m_mode);
}


void Me::Resources::GL::Mesh::GenerateBuffers()
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ibo);

    glBindVertexArray(m_vao);

    int vertBytes = sizeof(m_vertices);
    uint16_t indBytes = sizeof(m_indices);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, int(vertBytes * sizeof(Vertex)), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, uint16_t(indBytes * sizeof(uint16_t)), m_indices.data(), GL_STATIC_DRAW);

    GenerateAttributes();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void Me::Resources::GL::Mesh::GenerateAttributes()
{
    unsigned int offset = 0;
    int attributeId = 0;
    unsigned int values = 3;
    unsigned int stride = sizeof(Vertex);

    glVertexAttribPointer(attributeId, values, GL_FLOAT, GL_FALSE, stride, (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(attributeId);
}