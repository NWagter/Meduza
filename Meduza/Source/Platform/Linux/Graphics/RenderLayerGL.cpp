#include "MePCH.h"
#include "Platform/Linux/Graphics/RenderLayerGL.h"

#include "Platform/Linux/LinuxWindow.h"
#include "Platform/Linux/Context.h"

#include "Platform/Linux/Resources/Mesh.h"

Me::Renderer::GL::RenderLayerGL::RenderLayerGL(Window* a_window)
{
    if(a_window== nullptr)
    {
        printf("No Window! \n");
        return;
    }

    m_window = dynamic_cast<LinuxWindow*>(a_window);
    m_context = new Context();
    m_window->SetContext(m_context);
}
Me::Renderer::GL::RenderLayerGL::~RenderLayerGL()
{

}

void Me::Renderer::GL::RenderLayerGL::Clear(Colour a_colour)
{
    glViewport(0,0, m_context->m_width, m_context->m_height);
    glClearColor(a_colour.m_colour[0],
                 a_colour.m_colour[1],
                 a_colour.m_colour[2],
                 a_colour.m_colour[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Me::Renderer::GL::RenderLayerGL::Present()
{
    m_context->SwapBuffers();
}


void Me::Renderer::GL::RenderLayerGL::Submit(Renderable&)
{
    
}

Me::Resources::GL::Mesh* Me::Renderer::GL::RenderLayerGL::CreateMesh(std::vector<Vertex> a_vertices, std::vector<uint16_t> a_indices)
{
    return new Resources::GL::Mesh(a_vertices, a_indices);
}