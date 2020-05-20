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

    Instance instance;
    instance.m_vbo = helper::HelperGL::CreateEmptyVbo(14, &instance.m_data[0]);
    m_instances.push_back(instance);


// Instanced
    glBindVertexArray(m_quad->GetVAO());
    glBindBuffer(GL_ARRAY_BUFFER, m_instances[0].m_vbo);
    glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(InstanceData2D), (void*)(sizeof(float) * 0));
    glVertexAttribPointer(2, 4, GL_FLOAT, false, sizeof(InstanceData2D), (void*)(sizeof(float) * 4));
    glVertexAttribPointer(3, 4, GL_FLOAT, false, sizeof(InstanceData2D), (void*)(sizeof(float) * 8));
    glVertexAttribPointer(4, 4, GL_FLOAT, false, sizeof(InstanceData2D), (void*)(sizeof(float) * 11));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);

    // sent these attributes only once per instance to the program:
    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);

    glBindVertexArray(0);

    glBindBuffer(GL_UNIFORM_BUFFER, m_instances[0].m_vbo);
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
	PopulateBuffers();

// Reset the Instance buffers

    for (auto i : m_instances)
    {
        i.m_data.clear();
    }
    m_instances.clear();
    m_instanceID = 0;

    Instance instance;
    instance.m_vbo = helper::HelperGL::CreateEmptyVbo(14, &instance.m_data[0]);
    m_instances.push_back(instance);
}

void meduza::renderer::RendererGL::Draw(drawable::Drawable* a_drawable)
{
    if (m_instances.empty())
    {
        return;
    }

    auto drawData = a_drawable->GetDrawData();

    if (m_instances[m_instanceID].m_count >=  MAX_INSTANCES)
    {
        Instance instance;
        instance.m_vbo = helper::HelperGL::CreateEmptyVbo(14, &instance.m_data[0]);
        m_instances.push_back(instance);
        m_instanceID++;
    }

    if (m_instances[m_instanceID].m_shaderId <= 0)
    {
        m_instances[m_instanceID].m_shaderId = drawData->m_shaderId;
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

    math::Vec4 rect = { tC.x, tC.y, tC.z, tC.w };
    math::Vec2 size = { float(m_cachedTexture->GetWidth()), float(m_cachedTexture->GetHeight()) };
    math::Vec4 textCoord = utils::TextureUtils::GetTextureCoords(rect, size);

    data.m_textureCoords = glm::vec4(textCoord.m_x, textCoord.m_y, textCoord.m_z, textCoord.m_w);
    data.m_colour = drawData->m_colour;

    m_instances[m_instanceID].m_data[m_instances[m_instanceID].m_count] = data;
    m_instances[m_instanceID].m_count++;

    m_stats.m_drawables++;
}

void meduza::renderer::RendererGL::Submit(std::vector<drawable::Drawable*> a_drawables)
{
    if (m_instances.empty())
    {
        return;
    }

    for (auto d : a_drawables)
    {
        auto drawData = d->GetDrawData();
        m_stats.m_drawables++;

        if (m_instances[m_instanceID].m_count >= MAX_INSTANCES)
        {
            Instance instance;
            instance.m_vbo = helper::HelperGL::CreateEmptyVbo(14, &instance.m_data[0]);
            m_instances.push_back(instance);
            m_instanceID++;
        }

        if (m_instances[m_instanceID].m_shaderId <= 0)
        {
            m_instances[m_instanceID].m_shaderId = drawData->m_shaderId;
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

        math::Vec4 rect = { tC.x, tC.y, tC.z, tC.w };
        math::Vec2 size = { float(m_cachedTexture->GetWidth()), float(m_cachedTexture->GetHeight()) };
        math::Vec4 textCoord = utils::TextureUtils::GetTextureCoords(rect, size);

        data.m_textureCoords = glm::vec4(textCoord.m_x, textCoord.m_y, textCoord.m_z, textCoord.m_w);
        data.m_colour = drawData->m_colour;


        m_instances[m_instanceID].m_data[m_instances[m_instanceID].m_count] = data;
        m_instances[m_instanceID].m_count++;
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
        for (auto i : m_instances)
        {
            if (i.m_count <= 0)
            {
                continue;
            }

            unsigned int instances = i.m_count;
            m_stats.m_drawCalls++;
            m_stats.m_vertices += int(m_quad->GetVerticesSize() * instances);

            auto s = dynamic_cast<ShaderGL*>(ShaderLibrary::GetShader(i.m_shaderId));
            s->Bind();
            s->UploadUniformMat4("u_viewProjection", m_viewProjection);

            int slot = 0;
            m_cachedTexture->Bind(slot);
            dynamic_cast<ShaderGL*>(s)->UploadUniformInt("u_texture", slot);

            // upload instance buffer data:
            glBindBuffer(GL_UNIFORM_BUFFER, i.m_vbo);
            glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(InstanceData2D) * instances, i.m_data.data());
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
}

void meduza::renderer::RendererGL::PopulateBuffers()
{
    m_stats.Reset();
    PreRender();
}