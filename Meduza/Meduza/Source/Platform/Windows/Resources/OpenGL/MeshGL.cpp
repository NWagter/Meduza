#include "mePch.h"

#include "Core.h"

#include "Platform/Windows/Resources/OpenGL/MeshGL.h"

meduza::MeshGL::MeshGL(unsigned int a_id, std::vector<Vertex> a_vert, std::vector<uint16_t> a_ind, VertexAttributes a_atts, GLenum a_mode) : meduza::Mesh(a_id, a_vert, a_ind, a_atts)
{
    m_mode = a_mode;
	GenerateBuffers();
}

meduza::MeshGL::~MeshGL()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
}

void meduza::MeshGL::EnableMode()
{
    glPolygonMode(GL_FRONT_AND_BACK, m_mode);
}

void meduza::MeshGL::GenerateBuffers()
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ibo);


    glBindVertexArray(m_vao);

    int vertBytes = sizeof(m_vertices);
    int indBytes = sizeof(m_indices);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, int(vertBytes * sizeof(Vertex)), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, int(indBytes * sizeof(uint16_t)), m_indices.data(), GL_STATIC_DRAW);

    GenerateAttributes();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    EnableMode();
}

void meduza::MeshGL::GenerateAttributes()
{
    unsigned int offset = 0;
    unsigned int stride = m_attributes.GetStride();
    int attributeId = 0;

    for (std::pair<Attributes, int> a : m_attributes.GetAttributes())
    {
        unsigned int values = a.second;;
        glVertexAttribPointer(attributeId, values, GL_FLOAT, GL_FALSE, stride, (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(attributeId);
        attributeId++;
        offset += values;
    }
}
