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

#include "Platform/General/ResourceLibrary.h"

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
    m_quad = static_cast<Resource>(Primitives::Quad);
    Resources::ResourceLibrary* rLibrary = Resources::ResourceLibrary::GetInstance();
    m_screenShader = rLibrary->LoadResource<Resources::ShaderBase>("Resources/Shaders/!Shaders/GLFrameBuffer.glsl")->GetID();
    m_lineShader = rLibrary->LoadResource<Resources::ShaderBase>("Resources/Shaders/!Shaders/LineShader.glsl")->GetID();
    m_circleShader = rLibrary->LoadResource<Resources::ShaderBase>("Resources/Shaders/!Shaders/CircleShader.glsl")->GetID();
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

    delete m_frameBuffer;
    delete m_context;
    delete m_camera;
}

void Me::Renderer::GL::RenderLayerGL::Clear(Colour const a_clearColour)
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
    //m_instances.clear();

    for (auto i : m_debugInstances)
    {
        i->ClearBuffer();
    }
    //m_debugInstances.clear();

    m_frameBuffer->Bind();
    glViewport(0,0, m_context->m_width, m_context->m_height);
    glClearColor(a_clearColour.m_colour[0],
        a_clearColour.m_colour[1],
        a_clearColour.m_colour[2],
        a_clearColour.m_colour[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_activeShader = nullptr;

#ifdef EDITOR  
    m_renderStats.Reset(); 
#endif
}

void Me::Renderer::GL::RenderLayerGL::Present()
{
    Resources::ResourceLibrary* rLibrary = Resources::ResourceLibrary::GetInstance();
    
#ifndef EDITOR    
    auto s = static_cast<Resources::GL::Shader*>(rLibrary->GetResource<Resources::ShaderBase>(m_screenShader));
    auto m = static_cast<Resources::GL::Mesh*>(rLibrary->GetResource<Resources::MeshBase>(m_quad));
    
    s->Bind();

    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);
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
    Resources::ResourceLibrary* rLibrary = Resources::ResourceLibrary::GetInstance();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);

    for (auto i : m_instances)
    {
        if (i->Empty())
        {
            continue;
        }

        glEnable(GL_CULL_FACE);

        auto glI = static_cast<InstancedRenderCall<DefaultInstancedBuffer>*>(i);
        int vertSize = glI->Draw(m_camera->m_cameraMatrix);

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
        int vertSize = glI->Draw(m_camera->m_cameraMatrix);

#ifdef EDITOR  
        m_renderStats.m_drawCalls++;
        m_renderStats.m_vertices += vertSize * glI->Amount();
#endif
    }

    for (auto lines : m_debugLines)
    {
        auto s = static_cast<Resources::GL::Shader*>(rLibrary->GetResource<Resources::ShaderBase>(m_lineShader));

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
        auto s = static_cast<Resources::GL::Shader*>(rLibrary->GetResource<Resources::ShaderBase>(m_circleShader));
        auto m = static_cast<Resources::GL::Mesh*>(rLibrary->GetResource<Resources::MeshBase>(m_quad));
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

void Me::Renderer::GL::RenderLayerGL::Submit(RenderComponent const& a_renderComponent, TransformComponent const& a_transformComponent)
{
    // If no instanced Renderers we just create one
    BaseInstanced* instancedRenderer = nullptr;
    int texture = 0;

    if (m_instances.empty())
    {
        auto b = new InstancedRenderCall<DefaultInstancedBuffer>(a_renderComponent.m_mesh, a_renderComponent.m_shader);
        m_instances.push_back(b);
        texture = b->AddTexture(a_renderComponent.m_texture);

        instancedRenderer = b;
    }
    else
    {
        for (auto iR : m_instances)
        {
            auto glIR = static_cast<InstancedRenderCall<DefaultInstancedBuffer>*>(iR);
            texture = glIR->AddTexture(a_renderComponent.m_texture);

            if (a_renderComponent.m_mesh == glIR->GetMesh()
                && a_renderComponent.m_shader == glIR->GetShader()
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
            auto b = new InstancedRenderCall<DefaultInstancedBuffer>(a_renderComponent.m_mesh, a_renderComponent.m_shader);
            texture = b->AddTexture(a_renderComponent.m_texture);
            m_instances.push_back(b);

            instancedRenderer = b;
        }
    }

    auto iB = DefaultInstancedBuffer();

    Me::Colour colour = a_renderComponent.m_colour;
    iB.m_colour = colour.m_colour;
    iB.m_model = Math::Transpose(a_transformComponent.GetTransform());
    iB.m_textureCoords = a_renderComponent.m_textureCoords;
    iB.m_textureId = texture;

    static_cast<InstancedRenderCall<DefaultInstancedBuffer>*>(instancedRenderer)->AddData(iB);
}

void Me::Renderer::GL::RenderLayerGL::DebugSubmit(DebugRenderComponent const& a_debugRenderComponent, TransformComponent const& a_transformComponent)
{
    BaseInstanced* instancedRenderer = nullptr;

    if (m_debugInstances.empty())
    {
        auto b = new InstancedRenderCall<DefaultInstancedBuffer>(a_debugRenderComponent.m_mesh, a_debugRenderComponent.m_shader);
        m_debugInstances.push_back(b);

        instancedRenderer = b;
    }
    else
    {
        for (auto iR : m_debugInstances)
        {
            auto glIR = static_cast<InstancedRenderCall<DefaultInstancedBuffer>*>(iR);

            if (a_debugRenderComponent.m_mesh == glIR->GetMesh()
                && a_debugRenderComponent.m_shader == glIR->GetShader())
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
            auto b = new InstancedRenderCall<DefaultInstancedBuffer>(a_debugRenderComponent.m_mesh, a_debugRenderComponent.m_shader);
            m_debugInstances.push_back(b);

            instancedRenderer = b;
        }
    }

    auto iB = DefaultInstancedBuffer();

    Me::Colour colour = a_debugRenderComponent.m_debugColour;
    iB.m_colour = colour.m_colour;
    iB.m_model = Math::Transpose(a_transformComponent.GetTransform());

    static_cast<InstancedRenderCall<DefaultInstancedBuffer>*>(instancedRenderer)->AddData(iB);
}

void Me::Renderer::GL::RenderLayerGL::RenderLine(LineRender const& a_lineRender)
{
    if (!Debug::MeduzaDebug::GetDebuggingSettings().m_lineDebugger)
    {
        return;
    }

    unsigned int vao, vbo;
    std::vector<float> vertices = {
             a_lineRender.m_start.m_x, a_lineRender.m_start.m_y, a_lineRender.m_start.m_z,
             a_lineRender.m_end.m_x, a_lineRender.m_end.m_y, a_lineRender.m_end.m_z,

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
    m_debugLines.push_back(new DebugLine(vbo, vao, a_lineRender.m_colour));
}

void Me::Renderer::GL::RenderLayerGL::RenderCircle(CircleRender const& a_circleRender)
{
    if (!Debug::MeduzaDebug::GetDebuggingSettings().m_lineDebugger)
    {
        return;
    }
#ifdef EDITOR  
    m_renderStats.m_vertices += 1;
#endif
    
    m_debugCircle.push_back(new DebugCricle(a_circleRender.m_transform, a_circleRender.m_radius, a_circleRender.m_colour));
}

void Me::Renderer::GL::RenderLayerGL::SetCamera(CameraComponent const& a_cameraComponent, TransformComponent const& a_transformComponent)
{
    Math::Mat4 camMat = Math::Mat4::Identity();

    if(a_cameraComponent.m_cameraType == Me::CameraType::Orthographic)
    {
        Me::Math::Vec2 size = m_window->GetSize();
        float aspect = size.m_x / size.m_y;

        camMat = Math::GetOrthographicMatrix(-a_cameraComponent.m_orthoScale, a_cameraComponent.m_orthoScale,
            -a_cameraComponent.m_orthoScale * aspect , a_cameraComponent.m_orthoScale * aspect,
            a_cameraComponent.m_near, a_cameraComponent.m_far);
    }
    else
    {
        camMat = Math::GetProjectionMatrix(45.0f, a_cameraComponent.m_size.m_x / a_cameraComponent.m_size.m_y,
         a_cameraComponent.m_near, a_cameraComponent.m_far);
    }
    
    Math::Mat4 rMat = Math::Mat4::Identity();
    rMat.Rotation(a_transformComponent.m_rotation);

    Math::Mat4 pMat = Math::Mat4::Identity();
    pMat.SetPosition(a_transformComponent.m_translation);

    Math::Mat4 view = rMat * pMat.Inverse();

    Math::Mat4 camViewProjection = camMat * view;
    
    m_camera->m_cameraMatrix = Math::Transpose(camViewProjection);
}

Me::Resources::MeshBase* Me::Renderer::GL::RenderLayerGL::CreateMesh(std::vector<Vertex> const& a_vertices, std::vector<uint16_t> const& a_indices)
{
    return new Resources::GL::Mesh(a_vertices, a_indices);
}