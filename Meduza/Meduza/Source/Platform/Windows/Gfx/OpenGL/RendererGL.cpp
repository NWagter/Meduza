#include "mePch.h"

#include "Core.h"
#include "Drawable/Drawable.h"
#include "Platform/Windows/Utils/MeduzaHelper.h"

#include <glad/glad.h>

#include "Platform/Windows/Gfx/OpenGL/RendererGL.h"
#include "Platform/Windows/Window/OpenGL/ContextGL.h"

#include "Platform/Windows/Resources/OpenGL/MeshGL.h"

#include "Platform/General/Gfx/ShaderLibrary.h"
#include "Platform/Windows/Resources/OpenGL/ShaderGL.h"

#include "Platform/General/Gfx/TextureLibrary.h"
#include "Platform/General/Utils/TextureUtils.h"

#include "Camera/OrthographicCamera.h"

meduza::renderer::RendererGL::RendererGL(Context& a_context)
{
    m_context = dynamic_cast<ContextGL*>(&a_context);

	int status = gladLoadGL(); 
    ME_GFX_ASSERT_M(status, "Glad not loaded");
	std::string version = (char*)(glGetString(GL_VERSION));
    ME_GFX_LOG("OpenGl version : %s \n", version.c_str());

    glViewport(0, 0, int(a_context.GetSize().m_x), int(a_context.GetSize().m_y));

    std::vector<Vertex> vertices = {
    Vertex(-0.5f,  0.5f, 0.0f),   // top left 
    Vertex(0.5f ,  0.5f, 0.0f),  // top right
    Vertex(-0.5f, -0.5f, 0.0f),  // bottom left
    Vertex(0.5f, -0.5f, 0.0f),  // bottom right
    };
    std::vector<int> indices = {  // note that we start from 0!
       3, 1, 0,  // first Triangle
       3, 0, 2,   // second Triangle
    };

    VertexAttributes att;
    att.AddAttribute(Attributes::vec3Attribute);
    att.AddAttribute(Attributes::vec2Attribute);
    att.AddAttribute(Attributes::vec2Attribute);

    m_quad = new MeshGL(0, vertices, indices, att, GL_LINE);
}

meduza::renderer::RendererGL::~RendererGL()
{
    if (m_quad != nullptr)
    {
        delete m_quad;
    }
}

void meduza::renderer::RendererGL::Clear(Colour a_colour)
{
	glClearColor(a_colour.m_r, a_colour.m_g, a_colour.m_b, a_colour.m_a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void meduza::renderer::RendererGL::Render(const Camera& a_camera)
{
    m_viewProjection = a_camera.GetViewProjection();

	PopulateBuffers();

    m_drawData.clear();
}

void meduza::renderer::RendererGL::Draw(drawable::Drawable* a_drawable)
{
    auto d = a_drawable->GetDrawData();
    m_drawData.push_back(*d);
}

void meduza::renderer::RendererGL::Submit(std::vector<drawable::Drawable*> a_drawables)
{
    for (auto d : a_drawables)
    {
        m_drawData.push_back(*d->GetDrawData());
    }
}

void meduza::renderer::RendererGL::PreRender()
{
    if (m_quad != nullptr)
    {
        for (meduza::DrawData d : m_drawData)
        {
            auto s = dynamic_cast<ShaderGL*>(ShaderLibrary::GetShader(d.m_shaderId));
            s->Bind();
            s->UploadUniformMat4("u_viewProjection", m_viewProjection);
            s->UploadUniformVec3("u_position", d.m_position);
            s->UploadUniformVec3("u_size", d.m_size);
            s->UploadUniformVec4("u_colour", d.m_colour);
            if (d.m_textureId != 0)
            {
                auto t = TextureLibrary::GetTexture(d.m_textureId);
                int slot = 0;
                t->Bind(slot);
                auto tC = m_drawData[0].m_textCoords;

                math::Vec4 rect = { tC.x, tC.y, tC.z, tC.w };
                math::Vec2 size = { float(t->GetWidth()), float(t->GetHeight()) };
                dynamic_cast<ShaderGL*>(s)->UploadUniformInt("u_texture", slot);
                dynamic_cast<ShaderGL*>(s)->UploadUniformVec4("u_textureSpace",
                    utils::TextureUtils::GetTextureCoords(rect, size).m_xyzw);
            }

            glBindVertexArray(m_quad->GetVAO());
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            ShaderLibrary::GetShader(d.m_shaderId)->UnBind();
        }
    }
}

void meduza::renderer::RendererGL::PopulateBuffers()
{
    PreRender();
}