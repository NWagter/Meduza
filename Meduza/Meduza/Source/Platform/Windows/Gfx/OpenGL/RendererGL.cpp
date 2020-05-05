#include "mePch.h"

#include "Core.h"
#include "Drawable/Drawable.h"
#include "Util/MeduzaHelper.h"

#include <glad/glad.h>

#include "Platform/Windows/Gfx/OpenGL/RendererGL.h"
#include "Platform/Windows/Window/OpenGL/ContextGL.h"

#include "Platform/Windows/Resources/OpenGL/MeshGL.h"

#include "Platform/General/Gfx/ShaderLibrary.h"
#include "Platform/Windows/Resources/OpenGL/ShaderGL.h"

#include "Platform/General/Utils/TextureUtils.h"
#include "Platform/General/Resources/Texture.h"

meduza::renderer::RendererGL::RendererGL(Context& a_context)
{
    m_context = dynamic_cast<ContextGL*>(&a_context);

	int status = gladLoadGL(); 
    ME_GFX_ASSERT_M(status, "Glad not loaded");
	std::string version = (char*)(glGetString(GL_VERSION));
    ME_GFX_LOG("OpenGl version : %s \n", version.c_str());

    glViewport(0, 0, int(a_context.GetSize().m_x), int(a_context.GetSize().m_y));
    m_checkerBoard = Texture2D::Create("Data/Textures/sprites.png");
}

meduza::renderer::RendererGL::~RendererGL()
{
    delete m_checkerBoard;
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
        Vertex(-0.5f + d->m_position.x,  0.5f + +d->m_position.y, 0.0f, 0.f, 1.f),   // top left 
        Vertex(0.5f + d->m_position.x ,  0.5f + d->m_position.y, 0.0f, 1.f, 1.f),  // top right
        Vertex(-0.5f + d->m_position.x, -0.5f + d->m_position.y, 0.0f, 0.f, 0.f),  // bottom left
        Vertex(0.5f + d->m_position.x, -0.5f + d->m_position.y, 0.0f, 1.f, 0.f),  // bottom right
    };
    std::vector<int> indices = {  // note that we start from 0!
       3, 1, 0,  // first Triangle
       3, 0, 2,   // second Triangle
    };
    math::Vec4 uv = { d->m_textCoords.x,d->m_textCoords.y, d->m_textCoords.z,d->m_textCoords.w };
    math::Vec2 size = { float(m_checkerBoard->GetWidth()), float(m_checkerBoard->GetHeight()) };

    m_rect = utils::TextureUtils::GetTextureCoords(uv, size);

    m_drawData.push_back(*d);
    VertexAttributes att;
    att.AddAttribute(Attributes::vec3Attribute);
    att.AddAttribute(Attributes::vec2Attribute);
    att.AddAttribute(Attributes::vec2Attribute);

    m_quad = new MeshGL(0, vertices, indices, att, GL_LINE);
}

void meduza::renderer::RendererGL::Submit(std::vector<drawable::Drawable*>)
{
 
}

void meduza::renderer::RendererGL::PreRender()
{

    if (m_quad != nullptr)
    {
        ShaderLibrary::GetShader(m_drawData[0].m_shaderId)->Bind();
        
        m_checkerBoard->Bind(0);
        dynamic_cast<ShaderGL*>(ShaderLibrary::GetShader(m_drawData[0].m_shaderId))->UploadUniformInt("u_texture", 0);
        dynamic_cast<ShaderGL*>(ShaderLibrary::GetShader(m_drawData[0].m_shaderId))->UploadUniformVec4("u_textureSpace", m_rect.m_xyzw);

        glBindVertexArray(m_quad->GetVAO());
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        ShaderLibrary::GetShader(m_drawData[0].m_shaderId)->UnBind();
    }
}

void meduza::renderer::RendererGL::PopulateBuffers()
{
    PreRender();
}