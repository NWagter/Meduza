#include "mePch.h"
#include "Core/Core.h"
#include "Renderable/Renderable2D.h"

#ifdef WINDOWS

#include "Platform/Windows/Resources/OpenGL/MeshGL.h"
#include "Platform/Windows/Resources/Dx12/MeshDx12.h"

#endif

#include "Platform/General/Utils/MeduzaHelper.h"


meduza::Renderable2D::Renderable2D()
{
    CreateQuad();
    m_transform.SetUnitsPerPixel(m_pixelsPerUnit);
}

meduza::Renderable2D::Renderable2D(float a_pPU)
{
    CreateQuad();
    m_pixelsPerUnit = a_pPU;
    m_transform.SetUnitsPerPixel(m_pixelsPerUnit);
}

void meduza::Renderable2D::CreateQuad()
{
    // Generate Quad
    std::vector<Vertex> vertices = {
        Vertex(-0.5f,  0.5f, 0.0f),
        Vertex(0.5f ,  0.5f, 0.0f),
        Vertex(-0.5f, -0.5f, 0.0f),
        Vertex(0.5f, -0.5f, 0.0f)
    };
    std::vector<int> indices = {
        3, 1, 0,
        3, 0, 2
    };
    VertexAttributes att;
    att.AddAttribute(Attributes::vec3Attribute);

    switch (MeduzaHelper::ms_activeAPI)
    {
    case meduza::API::OpenGL:
        m_mesh = new MeshGL(0, vertices, indices, att);

        break;
    case meduza::API::DirectX12:
        m_mesh = new MeshDx12(0, vertices, indices, att);
        break;

    }
}

meduza::Renderable2D::~Renderable2D()
{

}

void meduza::Renderable2D::SetMesh(Mesh&)
{
    ME_CORE_LOG("Can't Set mesh on 2D Renderable!");
    return;
}

void meduza::Renderable2D::SetUnitsPerPixel(float a_uPP)
{
    m_transform.SetUnitsPerPixel(a_uPP);
}
