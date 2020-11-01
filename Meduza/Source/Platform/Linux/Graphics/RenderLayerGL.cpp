#include "MePCH.h"
#include "Platform/Linux/Graphics/RenderLayerGL.h"

#include "Platform/Linux/LinuxWindow.h"
#include "Platform/Linux/Context.h"

#include "Platform/Linux/Resources/Mesh.h"
#include "Platform/General/MeshLibrary.h"
#include "Platform/Linux/Resources/Shader.h"
#include "Platform/General/ShaderLibrary.h"

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
    m_activeShader = nullptr;
}
Me::Renderer::GL::RenderLayerGL::~RenderLayerGL()
{

}

void Me::Renderer::GL::RenderLayerGL::Clear(Colour a_colour)
{
    m_renderables.clear();
    glViewport(0,0, m_context->m_width, m_context->m_height);
    glClearColor(a_colour.m_colour[0],
                 a_colour.m_colour[1],
                 a_colour.m_colour[2],
                 a_colour.m_colour[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_activeShader = nullptr;
}

void Me::Renderer::GL::RenderLayerGL::Present()
{
    Populate();

    m_context->SwapBuffers();
}

void Me::Renderer::GL::RenderLayerGL::Populate()
{
    for (auto r : m_renderables)
    {
		auto s = static_cast<Resources::GL::Shader*>(Resources::ShaderLibrary::GetShader(r->m_shader));
        auto m = static_cast<Resources::GL::Mesh*>(Resources::MeshLibrary::GetMesh(r->m_mesh));

		if(m_activeShader == nullptr || m_activeShader != s) // only change when shader / pso changes
		{
			m_activeShader = s;
			m_activeShader->Bind();
		}
        glBindBuffer(GL_UNIFORM_BUFFER, m->GetVBO());
        glBindVertexArray(m->GetVAO());

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, m->GetIndicesSize(), 1);
        glBindVertexArray(0);
    }
    
}

void Me::Renderer::GL::RenderLayerGL::Submit(Renderable& a_renderable)
{
    m_renderables.push_back(&a_renderable);
}

Me::Resources::GL::Mesh* Me::Renderer::GL::RenderLayerGL::CreateMesh(std::vector<Vertex> a_vertices, std::vector<uint16_t> a_indices)
{
    return new Resources::GL::Mesh(a_vertices, a_indices);
}