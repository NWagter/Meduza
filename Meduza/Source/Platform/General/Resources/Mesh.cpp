#include "MePCH.h"
#include "Platform/General/Resources/Mesh.h"

Me::Resources::GL::Mesh::Mesh(std::vector<Vertex> const& a_vertices, std::vector<uint16_t> const& a_indices)
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
    glPolygonMode(GL_FRONT, m_mode);
}

void Me::Resources::GL::Mesh::GenerateBuffers()
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ibo);

    glBindVertexArray(m_vao);

    //int vertBytes = sizeof(m_vertices);
    //uint16_t indBytes = sizeof(m_indices);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint16_t), m_indices.data(), GL_STATIC_DRAW);

    GenerateAttributes();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Me::Resources::GL::Mesh::GenerateAttributes()
{
    unsigned int offset = 0;
    int attributeId = 0;
    unsigned int values = 3;
    unsigned int stride = sizeof(Vertex);

    glVertexAttribPointer(attributeId, values, GL_FLOAT, GL_FALSE, stride, (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(attributeId);

    attributeId++;
    offset += values;
    values = 3;

    glVertexAttribPointer(attributeId, values, GL_FLOAT, GL_FALSE, stride, (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(attributeId);

    attributeId++;
    offset += values;
    values = 2;

    glVertexAttribPointer(attributeId, values, GL_FLOAT, GL_FALSE, stride, (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(attributeId);
}