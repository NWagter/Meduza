#include "mePch.h"

#include "Core.h"
#include "Drawable/Drawable.h"
#include "Util/MeduzaHelper.h"

#include <glad/glad.h>

#include "Platform/Windows/Gfx/OpenGL/RendererGL.h"
#include "Platform/Windows/Window/OpenGL/ContextGL.h"

#include "Platform/Windows/Resources/OpenGL/MeshGL.h"

#include "Platform/General/Gfx/ShaderLibrary.h"


meduza::renderer::RendererGL::RendererGL(Context& a_context)
{
    m_context = dynamic_cast<ContextGL*>(&a_context);

	int status = gladLoadGL(); 
    ME_GFX_ASSERT_M(status, "Glad not loaded");
	std::string version = (char*)(glGetString(GL_VERSION));
    ME_GFX_LOG("OpenGl version : %s \n", version.c_str());

    glViewport(0, 0, int(a_context.GetSize().m_x), int(a_context.GetSize().m_y));
}

meduza::renderer::RendererGL::~RendererGL()
{
}

void meduza::renderer::RendererGL::Clear(Colour a_colour)
{
	glClearColor(a_colour.m_r, a_colour.m_g, a_colour.m_b, a_colour.m_a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void meduza::renderer::RendererGL::Render()
{
	PopulateBuffers();

    if (m_quad != nullptr)
    {
        delete m_quad;
    }

    m_drawData.clear();
}

void meduza::renderer::RendererGL::Draw(drawable::Drawable* a_drawable)
{
    auto d = a_drawable->GetDrawData();

    std::vector<Vertex> vertices = {
        Vertex(0.5f + d->m_position.x ,  0.5f + d->m_position.y, 0.0f),  // top right
        Vertex(0.5f + d->m_position.x, -0.5f + d->m_position.y, 0.0f),  // bottom right
        Vertex(-0.5f + d->m_position.x, -0.5f + d->m_position.y, 0.0f),  // bottom left
        Vertex(-0.5f + d->m_position.x,  0.5f + +d->m_position.y, 0.0f),   // top left 
    };
    std::vector<int> indices = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3,   // second Triangle
    };

    m_drawData.push_back(*d);
    m_quad = new MeshGL(0, vertices, indices, GL_LINE);
}

void meduza::renderer::RendererGL::Submit(std::vector<drawable::Drawable*>)
{
 
}

void meduza::renderer::RendererGL::PreRender()
{

    if (m_quad != nullptr)
    {
        ShaderLibrary::GetShader(m_drawData[0].m_shaderId)->Bind();
        glBindVertexArray(m_quad->GetVAO());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        ShaderLibrary::GetShader(m_drawData[0].m_shaderId)->UnBind();
    }
}

void meduza::renderer::RendererGL::PopulateBuffers()
{
    PreRender();
}