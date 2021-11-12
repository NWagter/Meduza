#include "MePCH.h"

#include "Platform/General/Graphics/RenderLayerGL.h"
#include "Platform/General/Window.h"

#include "Utils/MeduzaDebug.h"

#ifdef PLATFORM_LINUX
#include "Platform/Linux/Graphics/Context.h"
#elif PLATFORM_WINDOWS
#include "Platform/Windows/Graphics/ContextGL.h"
#endif

#include "Platform/General/Graphics/FramebufferGL.h"

#include "Platform/General/Resources/Mesh.h"
#include "Platform/General/Resources/Shader.h"
#include "Platform/General/Resources/Texture.h"

#include "Platform/General/MeshLibrary.h"
#include "Platform/General/ShaderLibrary.h"
#include "Platform/General/TextureLibrary.h"

#include "Core/Components/RenderComponent.h"
#include "Core/Components/CameraComponent.h"
#include "Core/Components/TransformComponent.h"

Me::Renderer::GL::RenderLayerGL::RenderLayerGL(Window* a_window)
{
    if(a_window== nullptr)
    {
        printf("No Window! \n");
        return;
    }

    m_window = a_window;
    m_context = new Context(*m_window);
    m_activeShader = nullptr;

    FrameBufferSpecs spec;
    spec.m_api = GFX_API::OpenGL;
    spec.m_size = m_window->GetSize();
    m_frameBuffer = FrameBuffer::Create(spec, *m_context);

    m_camera = new Camera();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glAlphaFunc(GL_GREATER, 0.6f);
    
    glCullFace(GL_FRONT); 
}

void Me::Renderer::GL::RenderLayerGL::Init()
{
    m_quad = Resources::MeshLibrary::GetMeshIndex(Primitives::Quad);
    m_screenShader = Resources::ShaderLibrary::CreateShader("Resources/Shaders/GLFrameBuffer.glsl");
    m_lineShader = Resources::ShaderLibrary::CreateShader("Resources/Shaders/LineShader.glsl");
}

Me::Renderer::GL::RenderLayerGL::~RenderLayerGL()
{
    for(auto r : m_renderables)
    {
        delete r;
    }
    m_renderables.clear();

    for(auto r : m_debugRenderables)
    {
        delete r;
    }
    m_debugRenderables.clear();

    delete m_context;
    delete m_camera;
}

void Me::Renderer::GL::RenderLayerGL::Clear(Colour a_colour)
{
    for (auto line : m_debugLines)
    {
        delete line;
    }
    m_debugLines.clear();

    for(auto r : m_renderables)
    {
        delete r;
    }
    m_renderables.clear();

    for(auto r : m_debugRenderables)
    {
        delete r;
    }
    m_debugRenderables.clear();


    m_frameBuffer->Bind();
    glViewport(0,0, m_context->m_width, m_context->m_height);
    glClearColor(a_colour.m_colour[0],
                 a_colour.m_colour[1],
                 a_colour.m_colour[2],
                 a_colour.m_colour[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_activeShader = nullptr;

#ifdef EDITOR  
    m_renderStats.Reset(); 
#endif
}

void Me::Renderer::GL::RenderLayerGL::Present()
{
#ifndef EDITOR    
    auto s = static_cast<Resources::GL::Shader*>(Resources::ShaderLibrary::GetShader(m_screenShader));
    auto m = static_cast<Resources::GL::Mesh*>(Resources::MeshLibrary::GetMesh(m_quad));
    
    s->Bind();

    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, static_cast<ColourAttachmentGL*>(m_frameBuffer->GetColourAttachment())->m_texture);
    glBindVertexArray(m->GetVAO());
    glDrawElementsInstanced(GL_TRIANGLES, m->GetIndices().size(), GL_UNSIGNED_SHORT, 0, 1);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);   
#endif

    m_context->SwapBuffer();
}

void Me::Renderer::GL::RenderLayerGL::Populate()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);

    for (auto r : m_renderables)
    {
        glEnable(GL_CULL_FACE);

        auto renderComp = r->m_renderComponent;
		auto s = static_cast<Resources::GL::Shader*>(Resources::ShaderLibrary::GetShader(renderComp->m_shader));
        auto m = static_cast<Resources::GL::Mesh*>(Resources::MeshLibrary::GetMesh(renderComp->m_mesh));
        auto t = static_cast<Resources::GL::Texture*>(Resources::TextureLibrary::GetTexture(renderComp->m_texture));

		if(m_activeShader == nullptr || m_activeShader != s) // only change when shader / pso changes
		{
            if(s != nullptr)
            {
                m_activeShader = s;
                m_activeShader->Bind();
            }
            else
            {
                continue;
            }
		}

        m_activeShader->SetMat4("u_model", r->m_modelMatrix, false);
        m_activeShader->SetMat4("u_projectionView", m_camera->m_cameraMatrix, false);

        m_activeShader->SetVec4("u_colour", Math::Vec4(renderComp->m_colour.m_colour));
        m_activeShader->SetVec4("u_uv", Math::Vec4(renderComp->m_textureCoords.m_xyzw));

        if(t != nullptr)
        {
            if(renderComp->m_mesh == (Mesh)Primitives::Quad)
            {
                glDisable(GL_CULL_FACE);
            }

            t->Bind();
        }
        
        glBindVertexArray(m->GetVAO());
        glDrawElementsInstanced(GL_TRIANGLES, m->GetIndices().size(), GL_UNSIGNED_SHORT, 0, 1);
#ifdef EDITOR  
        m_renderStats.m_drawCalls++;
#endif

        glBindVertexArray(0);
        t->UnBind();
    }

    glDisable(GL_ALPHA_TEST);
    glDisable(GL_DEPTH_TEST);

    for(auto r : m_debugRenderables)
    {

        auto renderComp = r->m_debugRenderComponent;        
		auto s = static_cast<Resources::GL::Shader*>(Resources::ShaderLibrary::GetShader(renderComp->m_shader));
        auto m = static_cast<Resources::GL::Mesh*>(Resources::MeshLibrary::GetMesh(renderComp->m_mesh));

        if(m_activeShader == nullptr || m_activeShader != s) // only change when shader / pso changes
		{
            if(s != nullptr)
            {
                m_activeShader = s;
                m_activeShader->Bind();
            }
            else
            {
                continue;
            }
		}
        
        m_activeShader->SetMat4("u_model", r->m_modelMatrix, false);
        m_activeShader->SetMat4("u_projectionView", m_camera->m_cameraMatrix, false);

        m_activeShader->SetVec4("u_colour", Math::Vec4(renderComp->m_debugColour.m_colour));

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glBindVertexArray(m->GetVAO());
        glDrawElementsInstanced(GL_TRIANGLES, m->GetIndices().size(), GL_UNSIGNED_SHORT, 0, 1);
        glBindVertexArray(0);

#ifdef EDITOR  
        m_renderStats.m_drawCalls++;
#endif
    }

    for (auto lines : m_debugLines)
    {
        auto s = static_cast<Resources::GL::Shader*>(Resources::ShaderLibrary::GetShader(m_lineShader));

        if (m_activeShader == nullptr || m_activeShader != s) // only change when shader / pso changes
        {
            if (s != nullptr)
            {
                m_activeShader = s;
                m_activeShader->Bind();
            }
            else
            {
                continue;
            }
        }

        m_activeShader->SetMat4("u_projectionView", m_camera->m_cameraMatrix, false);
        m_activeShader->SetVec4("u_colour", Math::Vec4(lines->m_colour.m_colour));

        glBindVertexArray(lines->m_vao);
        glDrawArrays(GL_LINES, 0, 2);

#ifdef EDITOR  
        m_renderStats.m_drawCalls++;
#endif
    }
    
    m_frameBuffer->UnBind();
}

void Me::Renderer::GL::RenderLayerGL::Submit(RenderComponent& a_renderable, TransformComponent& a_trans)
{
    Renderable* r = new Renderable();
    r->m_renderComponent = &a_renderable;
    //r->m_modelMatrix = Math::Transpose(a_trans.GetTransform());

    r->m_modelMatrix = Math::Transpose(a_trans.GetTransform());

#ifdef EDITOR  
    auto m = static_cast<Resources::GL::Mesh*>(Resources::MeshLibrary::GetMesh(a_renderable.m_mesh));
    m_renderStats.m_vertices += m->GetVerticesSize();
#endif

    m_renderables.push_back(r);
}

void Me::Renderer::GL::RenderLayerGL::DebugSubmit(DebugRenderComponent& a_renderable, TransformComponent& a_trans)
{
    if (!Debug::MeduzaDebug::GetDebuggingSettings().m_collisionDebugger)
    {
        return;
    }

    DebugRenderable* r = new DebugRenderable();
    r->m_debugRenderComponent = &a_renderable;
    r->m_modelMatrix = Math::Transpose(a_trans.GetTransform());

#ifdef EDITOR  
    auto m = static_cast<Resources::GL::Mesh*>(Resources::MeshLibrary::GetMesh(a_renderable.m_mesh));
    m_renderStats.m_vertices += m->GetVerticesSize();
#endif

    m_debugRenderables.push_back(r);
}

void Me::Renderer::GL::RenderLayerGL::RenderLine(LineRender& a_line)
{
    if (!Debug::MeduzaDebug::GetDebuggingSettings().m_lineDebugger)
    {
        return;
    }

    unsigned int vao, vbo;
    std::vector<float> vertices = {
             a_line.m_start.m_x, a_line.m_start.m_y, a_line.m_start.m_z,
             a_line.m_end.m_x, a_line.m_end.m_y, a_line.m_end.m_z,

    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
#ifdef EDITOR  
    m_renderStats.m_vertices += vertices.size();
#endif
    m_debugLines.push_back(new DebugLine(vbo, vao, a_line.m_colour));
}

void Me::Renderer::GL::RenderLayerGL::SetCamera(CameraComponent& a_cameraComp, TransformComponent& a_transComp)
{
    Math::Mat4 camMat = Math::Mat4::Identity();

    if(a_cameraComp.m_cameraType == Me::CameraType::Orthographic)
    {
        Me::Math::Vec2 size = m_window->GetSize();
        float aspect = size.m_x / size.m_y;

        camMat = Math::GetOrthographicMatrix(-a_cameraComp.m_orthoScale, a_cameraComp.m_orthoScale,
            -a_cameraComp.m_orthoScale * aspect , a_cameraComp.m_orthoScale * aspect,
            a_cameraComp.m_near, a_cameraComp.m_far);
    }
    else
    {
        camMat = Math::GetProjectionMatrix(45.0f, a_cameraComp.m_size.m_x / a_cameraComp.m_size.m_y,
         a_cameraComp.m_near, a_cameraComp.m_far);
    }
    
    Math::Mat4 rMat = Math::Mat4::Identity();
    rMat.Rotation(a_transComp.m_rotation);

    Math::Mat4 pMat = Math::Mat4::Identity();
    pMat.SetPosition(a_transComp.m_translation);

    Math::Mat4 view = rMat * pMat.Inverse();

    Math::Mat4 camViewProjection = camMat * view;
    
    m_camera->m_cameraMatrix = Math::Transpose(camViewProjection);
}

Me::Resources::GL::Mesh* Me::Renderer::GL::RenderLayerGL::CreateMesh(std::string a_path, std::vector<Vertex> a_vertices, std::vector<uint16_t> a_indices)
{
    return new Resources::GL::Mesh(a_path, a_vertices, a_indices);
}