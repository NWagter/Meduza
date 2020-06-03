#include "mePch.h"

#include "Core.h"
#include "Drawable/Drawable.h"
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

    m_quad = new MeshGL(0, vertices, indices, att, GL_LINE);

    m_vbo = helper::HelperGL::CreateEmptyVbo(14, &m_instances[0]);

// Instanced
    glBindVertexArray(m_quad->GetVAO());
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(InstanceData2D), (void*)(sizeof(float) * 0));
    glVertexAttribPointer(2, 4, GL_FLOAT, false, sizeof(InstanceData2D), (void*)(sizeof(float) * 4));
    glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(InstanceData2D), (void*)(sizeof(float) * 8));
    glVertexAttribPointer(4, 3, GL_FLOAT, false, sizeof(InstanceData2D), (void*)(sizeof(float) * 11));
    glVertexAttribPointer(5, 1, GL_FLOAT, false , sizeof(InstanceData2D), (void*)(sizeof(float) * 14));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);

    // sent these attributes only once per instance to the program:
    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);

    glBindVertexArray(0);

    glBindBuffer(GL_UNIFORM_BUFFER, m_vbo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(InstanceData2D) * MAX_INSTANCES, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
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
    m_camPos = a_camera.GetEyePos();
	PopulateBuffers();

// Reset the Instance buffers

    m_drawData.clear();
    m_instances.clear();
    m_textures.clear();
    m_instances.resize(MAX_INSTANCES);

    m_count = 0;
}

void meduza::renderer::RendererGL::Draw(drawable::Drawable* a_drawable)
{
    auto drawData = a_drawable->GetDrawData();
    m_stats.m_drawables++;

    if (Cull(math::Vec2(drawData->m_position.x, drawData->m_position.y), math::Vec2(drawData->m_size.x, drawData->m_size.y)))
    {
        m_drawData.push_back(drawData);
    }

}

void meduza::renderer::RendererGL::Submit(std::vector<drawable::Drawable*> a_drawables)
{
    for (auto d : a_drawables)
    {
        auto drawData = d->GetDrawData();
        m_stats.m_drawables++;

        if (Cull(math::Vec2(drawData->m_position.x, drawData->m_position.y), math::Vec2(drawData->m_size.x, drawData->m_size.y)))
        {
            m_drawData.push_back(drawData);
        }
    }
}

meduza::renderer::DrawStatistics meduza::renderer::RendererGL::GetDrawStatistics() const
{
    return m_stats;
}

void meduza::renderer::RendererGL::PreRender()
{
    if (m_quad != nullptr)
    {      
        unsigned int instances = m_count;
        m_stats.m_drawCalls++;
        m_stats.m_vertices += int(m_quad->GetVerticesSize() * instances);

        auto s = dynamic_cast<ShaderGL*>(ShaderLibrary::GetShader(m_shaderID));
        s->Bind();
        s->UploadUniformMat4("u_viewProjection", m_viewProjection);

        int slot = 0;
        for (auto t : m_textures)
        {
            t->Bind(slot);
            std::string location = "u_texture[" + std::to_string(slot) + "]";
            s->UploadUniformInt(location, slot);
            slot++;
        }

        // upload instance buffer data:
        glBindBuffer(GL_UNIFORM_BUFFER, m_vbo);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(InstanceData2D) * instances, m_instances.data());
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        glBindVertexArray(m_quad->GetVAO());
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // render objects in scene
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, m_quad->GetVerticesSize(), instances);

        s->UnBind();
        glBindVertexArray(0);
    }
}

void meduza::renderer::RendererGL::PopulateBuffers()
{
    m_stats.Reset();
    CreateInstances();
    PreRender();
}

void meduza::renderer::RendererGL::CreateInstances()
{
    for (auto drawData : m_drawData)
    {

        if (m_count >= MAX_INSTANCES)
        {
            break;
        }

        if (m_shaderID <= 0)
        {
            m_shaderID = drawData->m_shaderId;
        }

        InstanceData2D data;

        data.m_position = drawData->m_position;
        data.m_size = drawData->m_size;

        auto tC = drawData->m_textCoords;

        if (m_textureId != drawData->m_textureId)
        {
            m_textureId = drawData->m_textureId;
            m_cachedTexture = TextureLibrary::GetTexture(drawData->m_textureId);      
        }

        float textureID = 0;
        bool exists = false;
        for (auto t : m_textures)
        {
            if (textureID >= MAX_TEXTURES)
            {
                ME_GFX_LOG("Can only use 16 differt textures currently!");
                textureID = 0;
                exists = true;
                break;
            }

            if (t == m_cachedTexture)
            {
                exists = true;
                break;
            }
            textureID++;
        }
        if (!exists)
        {
            m_textures.push_back(m_cachedTexture);
        }

        math::Vec4 rect = { tC.x, tC.y, tC.z, tC.w };
        math::Vec2 size = { float(m_cachedTexture->GetWidth()), float(m_cachedTexture->GetHeight()) };
        math::Vec4 textCoord = utils::TextureUtils::GetTextureCoords(rect, size);

        data.m_textureCoords = glm::vec4(textCoord.m_x, textCoord.m_y, textCoord.m_z, textCoord.m_w);
        data.m_colour = drawData->m_colour;
        data.m_textureId = textureID;

        m_instances[m_count] = data;
        m_count++;
    }
    m_stats.m_instances = m_count;
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
