#include "MePCH.h"

#include "Platform/General/Graphics/RenderLayerGL.h"

#ifdef PLATFORM_LINUX
#include "Platform/Linux/Graphics/Context.h"

#include "Platform/Linux/Resources/Mesh.h"

#include "Platform/Linux/Resources/Shader.h"


#include "Platform/Linux/Resources/Texture.h"

#elif PLATFORM_WINDOWS

#include "Platform/Windows/Graphics/ContextGL.h"

#endif

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

    m_camera = new Camera();
    glEnable(GL_DEPTH_TEST);

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
    m_context->SwapBuffer();
}

void Me::Renderer::GL::RenderLayerGL::Populate()
{

    #ifdef PLATFORM_LINUX
    for (auto r : m_renderables)
    {
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
		}

        m_activeShader->SetMat4("u_model", r->m_modelMatrix, false);
        m_activeShader->SetMat4("u_projectionView", m_camera->m_cameraMatrix, false);

        m_activeShader->SetVec4("u_colour", Math::Vec4(renderComp->m_colour.m_colour));

        if(t != nullptr)
        {
            t->Bind();
        }


        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glBindVertexArray(m->GetVAO());
        glDrawElementsInstanced(GL_TRIANGLES, m->GetIndices().size(), GL_UNSIGNED_SHORT, 0, 1);

        //glBindVertexArray(0);
    }
    #endif
    
}

void Me::Renderer::GL::RenderLayerGL::Submit(RenderComponent& a_renderable, TransformComponent& a_trans)
{
    Renderable* r = new Renderable();
    r->m_renderComponent = &a_renderable;
    //r->m_modelMatrix = Math::Transpose(a_trans.GetTransform());

    Math::Mat4 pMat = Math::Mat4::Identity();
    pMat.SetPosition(a_trans.GetPosition());

    Math::Mat4 rMat = Math::Mat4::Identity();
    rMat.Rotation(a_trans.GetRotation());

    Math::Mat4 sMat = Math::Mat4::Identity();
    sMat.SetScale(a_trans.GetUniformedScale());

    Math::Mat4 model = pMat * rMat * sMat;
    r->m_modelMatrix = Math::Transpose(model);

    m_renderables.push_back(r);
}

void Me::Renderer::GL::RenderLayerGL::SetCamera(CameraComponent& a_cameraComp, TransformComponent& a_transComp)
{
    Math::Mat4 camMat = Math::Mat4::Identity();

    if(a_cameraComp.m_cameraType == Me::CameraType::Orthographic)
    {
        camMat = Math::GetOrthographicMatrix(0, a_cameraComp.m_size.m_y,
            0 , a_cameraComp.m_size.m_x,
            a_cameraComp.m_near, a_cameraComp.m_far);
    }
    else
    {
        camMat = Math::GetProjectionMatrix(45.0f, a_cameraComp.m_size.m_x / a_cameraComp.m_size.m_y,
         a_cameraComp.m_near, a_cameraComp.m_far);
    }
    
    Math::Mat4 rMat = Math::Mat4::Identity();
    rMat.Rotation(a_transComp.GetRotation());

    Math::Mat4 pMat = Math::Mat4::Identity();
    pMat.SetPosition(a_transComp.GetPosition());

    Math::Mat4 view = rMat * pMat;

    Math::Mat4 camViewProjection = camMat * view;
    
    m_camera->m_cameraMatrix = Math::Transpose(camViewProjection);
}

Me::Resources::GL::Mesh* Me::Renderer::GL::RenderLayerGL::CreateMesh(std::vector<Vertex> a_vertices, std::vector<uint16_t> a_indices)
{
#ifdef PLATFORM_LINUX
    return new Resources::GL::Mesh(a_vertices, a_indices);
#else
    return nullptr;
#endif
}