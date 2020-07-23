#include "mePch.h"

#include "Core.h"

#include "Scene/Scene.h"
#include "Renderable/Renderable.h"

#include "Platform/General/Resources/Material.h"

#include "Platform/General/Utils/MeduzaHelper.h"
#include "Platform/Windows/Utils/OpenGL/HelperGL.h"

#include <glad/glad.h>

#include "Platform/Windows/Gfx/OpenGL/RendererGL.h"
#include "Platform/Windows/Window/OpenGL/ContextGL.h"

#include "Platform/Windows/Resources/OpenGL/MeshGL.h"

#include "Platform/General/Gfx/ShaderLibrary.h"
#include "Platform/Windows/Resources/OpenGL/ShaderGL.h"

#include "Platform/General/Gfx/TextureLibrary.h"
#include "Platform/General/Utils/TextureUtils.h"

#include "Camera/OrthographicCamera.h"

#define MINIMAL_MAJOR_VERSION 4
#define MINIMAL_MINOR_VERSION 5

meduza::renderer::RendererGL::RendererGL(Context& a_context)
{
    m_context = dynamic_cast<ContextGL*>(&a_context);

	int status = gladLoadGL(); 
    ME_GFX_ASSERT_M(status, "Glad not loaded");
	std::string version = (char*)(glGetString(GL_VERSION));

    int versionMajor;
    int versionMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

    if (versionMajor == MINIMAL_MAJOR_VERSION && versionMinor < MINIMAL_MINOR_VERSION)
    {
        ME_GFX_LOG("GL version not compadible only 4.5+ available, Your version is %i.%i \n", versionMajor, versionMinor);
        ME_GFX_ASSERT_M(0, "GL version not compadible only 4.5+ available, Your version is %f \n");
    }

    ME_GFX_LOG("OpenGl version : %s \n", version.c_str());

    glViewport(0, 0, int(a_context.GetSize().m_x), int(a_context.GetSize().m_y));
}

meduza::renderer::RendererGL::~RendererGL()
{
    
}

void meduza::renderer::RendererGL::Clear(Colour a_colour)
{
    m_renderables.clear();

	glClearColor(a_colour.m_r, a_colour.m_g, a_colour.m_b, a_colour.m_a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void meduza::renderer::RendererGL::Render(const Camera& a_camera)
{
    m_viewProjection = a_camera.GetViewProjection();
    m_camPos = a_camera.GetEyePos();

	PopulateBuffers();
}

void meduza::renderer::RendererGL::Submit(Renderable& a_renderable)
{
    m_stats.m_drawables++;

   auto position = a_renderable.GetTransform().Position();
   auto scale = a_renderable.GetTransform().GetPixelScale();

    if (Cull(math::Vec2(position.m_x, position.m_y), math::Vec2(scale.m_x, scale.m_y)))
    {
        m_renderables.push_back(&a_renderable);
    }
}

void meduza::renderer::RendererGL::Submit(Scene& a_scene)
{
    for (auto r : a_scene.GetRenderables())
    {
        Submit(*r);
    }
}

meduza::renderer::DrawStatistics meduza::renderer::RendererGL::GetDrawStatistics() const
{
    return m_stats;
}

void meduza::renderer::RendererGL::PreRender()
{
    meduza::Material* lastMat = nullptr;
    meduza::MeshGL* lastMesh = nullptr;

    for (auto r : m_renderables)
    {
        m_stats.m_drawCalls++;
        m_stats.m_vertices += int(r->GetMesh().GetVerticesSize());

        if (m_lastShader == nullptr || r->GetMaterial().GetShaderID() != m_lastShader->GetId())
        {
            m_lastShader = dynamic_cast<ShaderGL*>(ShaderLibrary::GetShader(r->GetMaterial().GetShaderID()));
        }

        if (lastMat == nullptr || lastMat != &r->GetMaterial())
        {
            lastMat = &r->GetMaterial();
        }

        if (lastMesh == nullptr || lastMesh != &r->GetMesh())
        {
            lastMesh = dynamic_cast<MeshGL*>(&r->GetMesh());

        }

        m_lastShader->Bind();

        auto c = lastMat->GetData("a_colour");
        glm::vec4 colour = glm::vec4(c.at(0), c.at(1), c.at(2), c.at(3));
        auto p = r->GetTransform().Position();
        glm::vec3 position = glm::vec3(p.m_x,p.m_y,p.m_z);
        auto s = r->GetTransform().GetPixelScale();
        glm::vec3 scale = glm::vec3(s.m_x, s.m_y, s.m_z);

        m_lastShader->UploadUniformMat4("u_viewProjection", m_viewProjection);
        m_lastShader->UploadUniformVec4("u_colour", colour);
        m_lastShader->UploadUniformVec3("u_pos", position);
        m_lastShader->UploadUniformVec3("u_scale", scale);


        // upload instance buffer data:
        glBindBuffer(GL_UNIFORM_BUFFER, lastMesh->GetVBO());
        glBindVertexArray(lastMesh->GetVAO());
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // render objects in scene
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, lastMesh->GetIndicesSize(), 1);

    }
}

void meduza::renderer::RendererGL::PopulateBuffers()
{
    m_stats.Reset();
    PreRender();
}

bool meduza::renderer::RendererGL::Cull(math::Vec2 a_pos, math::Vec2 a_size)
{
    math::Vec2 size = m_context->GetSize() / 2;

    if ((a_pos.m_x + a_size.m_x) < m_camPos.m_x - size.m_x || (a_pos.m_x - a_size.m_x) > m_camPos.m_x + size.m_x)
    {
        return false;
    }

    if ((a_pos.m_y + a_size.m_y) < m_camPos.m_y - size.m_y || (a_pos.m_y - a_size.m_y) > m_camPos.m_y + size.m_y)
    {
        return false;
    }

    return true;
}
