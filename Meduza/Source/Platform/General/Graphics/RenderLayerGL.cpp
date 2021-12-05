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

#include "Platform/General/Graphics/InstancedRenderCallGL.h"

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
    m_screenShader = Resources::ShaderLibrary::CreateShader("Resources/Shaders/!Shaders/GLFrameBuffer.glsl");
    m_lineShader = Resources::ShaderLibrary::CreateShader("Resources/Shaders/!Shaders/LineShader.glsl");
    m_circleShader = Resources::ShaderLibrary::CreateShader("Resources/Shaders/!Shaders/CircleShader.glsl");
}

Me::Renderer::GL::RenderLayerGL::~RenderLayerGL()
{
    for(auto r : m_debugCircle)
    {
        delete r;
    }
    m_debugCircle.clear();

    for (auto line : m_debugLines)
    {
        delete line;
    }
    m_debugLines.clear();

    for (auto i : m_instances)
    {
        delete i;
    }
    m_instances.clear();
    for (auto i : m_debugInstances)
    {
        delete i;
    }
    m_debugInstances.clear();

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

    for (auto r : m_debugCircle)
    {
        delete r;
    }
    m_debugCircle.clear();

    for (auto i : m_instances)
    {
        i->ClearBuffer();
    }
    for (auto i : m_debugInstances)
    {
        i->ClearBuffer();
    }

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

    for (auto i : m_instances)
    {
        glEnable(GL_CULL_FACE);

        auto glI = static_cast<InstancedRenderCall<DefaultInstancedBuffer>*>(i);

        //auto renderComp = r->m_renderComponent;
		auto s = static_cast<Resources::GL::Shader*>(Resources::ShaderLibrary::GetShader(i->GetShader()));

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

        m_activeShader->SetMat4("u_projectionView", m_camera->m_cameraMatrix, false);
        int vertSize = glI->Draw();
        glBindVertexArray(0);

#ifdef EDITOR  
        m_renderStats.m_drawCalls++;
        m_renderStats.m_vertices += vertSize * glI->Amount();
#endif
    }

    glDisable(GL_ALPHA_TEST);
    glDisable(GL_DEPTH_TEST);

    for (auto i : m_debugInstances)
    {
        glEnable(GL_CULL_FACE);

        auto glI = static_cast<InstancedRenderCall<DefaultInstancedBuffer>*>(i);

        //auto renderComp = r->m_renderComponent;
        auto s = static_cast<Resources::GL::Shader*>(Resources::ShaderLibrary::GetShader(i->GetShader()));

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
        int vertSize = glI->Draw(true);
        glBindVertexArray(0);
        //t->UnBind();

#ifdef EDITOR  
        m_renderStats.m_drawCalls++;
        m_renderStats.m_vertices += vertSize * glI->Amount();
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

    for (auto circle : m_debugCircle)
    {
        auto s = static_cast<Resources::GL::Shader*>(Resources::ShaderLibrary::GetShader(m_circleShader));
        auto m = static_cast<Resources::GL::Mesh*>(Resources::MeshLibrary::GetMesh(m_quad));
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

        m_activeShader->SetMat4("u_model", circle->m_trans, true);
        m_activeShader->SetMat4("u_projectionView", m_camera->m_cameraMatrix, false);
        m_activeShader->SetFloat("u_radius", circle->m_radius);
        m_activeShader->SetVec4("u_colour", Math::Vec4(circle->m_colour.m_colour));

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBindVertexArray(m->GetVAO());
        glDrawElementsInstanced(GL_TRIANGLES, m->GetIndices().size(), GL_UNSIGNED_SHORT, 0, 1);
        glBindVertexArray(0);

#ifdef EDITOR  
        m_renderStats.m_drawCalls++;
#endif
    }
    
    m_frameBuffer->UnBind();
}

void Me::Renderer::GL::RenderLayerGL::Submit(RenderComponent& a_renderable, TransformComponent& a_trans)
{
    // If no instanced Renderers we just create one
    BaseInstanced* instancedRenderer = nullptr;
    int texture = 0;

    if (m_instances.empty())
    {
        auto b = new InstancedRenderCall<DefaultInstancedBuffer>(a_renderable.m_mesh, a_renderable.m_shader);
        m_instances.push_back(b);
        texture = b->AddTexture(a_renderable.m_texture);

        instancedRenderer = b;
    }
    else
    {
        for (auto iR : m_instances)
        {
            auto glIR = static_cast<InstancedRenderCall<DefaultInstancedBuffer>*>(iR);
            texture = glIR->AddTexture(a_renderable.m_texture);

            if (a_renderable.m_mesh == glIR->GetMesh()
                && a_renderable.m_shader == glIR->GetShader()
                && texture != -1)
            {
                if (!glIR->ReachedMaxSize())
                {
                    instancedRenderer = iR;
                    break;
                }
            }
        }

        if (instancedRenderer == nullptr)
        {
            auto b = new InstancedRenderCall<DefaultInstancedBuffer>(a_renderable.m_mesh, a_renderable.m_shader);
            texture = b->AddTexture(a_renderable.m_texture);
            m_instances.push_back(b);

            instancedRenderer = b;
        }
    }

    Renderable* r = new Renderable();
    r->m_renderComponent = &a_renderable;

    auto iB = DefaultInstancedBuffer();

    iB.m_colour = a_renderable.m_colour.m_colour;
    iB.m_model = Math::Transpose(a_trans.GetTransform());
    iB.m_textureCoords = a_renderable.m_textureCoords;
    iB.m_textureId = texture;

    static_cast<InstancedRenderCall<DefaultInstancedBuffer>*>(instancedRenderer)->AddData(iB);
}

void Me::Renderer::GL::RenderLayerGL::DebugSubmit(DebugRenderComponent& a_renderable, TransformComponent& a_trans)
{
    BaseInstanced* instancedRenderer = nullptr;

    if (m_debugInstances.empty())
    {
        auto b = new InstancedRenderCall<DefaultInstancedBuffer>(a_renderable.m_mesh, a_renderable.m_shader);
        m_debugInstances.push_back(b);

        instancedRenderer = b;
    }
    else
    {
        for (auto iR : m_debugInstances)
        {
            auto glIR = static_cast<InstancedRenderCall<DefaultInstancedBuffer>*>(iR);

            if (a_renderable.m_mesh == glIR->GetMesh()
                && a_renderable.m_shader == glIR->GetShader())
            {
                if (!glIR->ReachedMaxSize())
                {
                    instancedRenderer = iR;
                    break;
                }
            }
        }

        if (instancedRenderer == nullptr)
        {
            auto b = new InstancedRenderCall<DefaultInstancedBuffer>(a_renderable.m_mesh, a_renderable.m_shader);
            m_debugInstances.push_back(b);

            instancedRenderer = b;
        }
    }

    DebugRenderable* r = new DebugRenderable();
    r->m_debugRenderComponent = &a_renderable;

    auto iB = DefaultInstancedBuffer();

    iB.m_colour = a_renderable.m_debugColour.m_colour;
    iB.m_model = Math::Transpose(a_trans.GetTransform());

    static_cast<InstancedRenderCall<DefaultInstancedBuffer>*>(instancedRenderer)->AddData(iB);
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
    m_renderStats.m_vertices += 2;
#endif
    m_debugLines.push_back(new DebugLine(vbo, vao, a_line.m_colour));
}

void Me::Renderer::GL::RenderLayerGL::RenderCircle(CircleRender& a_circle)
{
    if (!Debug::MeduzaDebug::GetDebuggingSettings().m_lineDebugger)
    {
        return;
    }
#ifdef EDITOR  
    m_renderStats.m_vertices += 1;
#endif
    
    m_debugCircle.push_back(new DebugCricle(a_circle.m_transform, a_circle.m_radius, a_circle.m_colour));
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