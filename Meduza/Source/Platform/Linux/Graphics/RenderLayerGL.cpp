#include "MePCH.h"
#include "Platform/Linux/Graphics/RenderLayerGL.h"

#include "Platform/Linux/LinuxWindow.h"
#include "Platform/Linux/Context.h"

#include "Platform/Linux/Resources/Mesh.h"
#include "Platform/General/MeshLibrary.h"

#include "Platform/Linux/Resources/Shader.h"
#include "Platform/General/ShaderLibrary.h"


#include "Platform/Linux/Resources/Texture.h"
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

    m_window = dynamic_cast<LinuxWindow*>(a_window);
    m_context = new Context();
    m_window->SetContext(m_context);
    m_activeShader = nullptr;

    m_cameraMat = new Math::Mat4();

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
    m_context->SwapBuffers();
}

void Me::Renderer::GL::RenderLayerGL::Populate()
{
    for (auto r : m_renderables)
    {
        auto renderComp = r->m_renderComponent;
		auto s = static_cast<Resources::GL::Shader*>(Resources::ShaderLibrary::GetShader(renderComp->m_shader));
        auto m = static_cast<Resources::GL::Mesh*>(Resources::MeshLibrary::GetMesh(renderComp->m_mesh));
        auto t = static_cast<Resources::GL::Texture*>(Resources::TextureLibrary::GetTexture(renderComp->m_texture));

		if(m_activeShader == nullptr || m_activeShader != s) // only change when shader / pso changes
		{
			m_activeShader = s;
			m_activeShader->Bind();
		}

        glBindBuffer(GL_UNIFORM_BUFFER, m->GetVBO());


        m_activeShader->SetMat4("u_model", r->m_modelMatrix, true);
        m_activeShader->SetMat4("u_projectionView", *m_cameraMat, true);
        
        m_activeShader->SetVec4("u_colour", Math::Vec4(renderComp->m_colour.m_colour));


        glBindVertexArray(m->GetVAO());

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, m->GetIndicesSize(), 1);
        glBindVertexArray(0);
    }
    
}

void Me::Renderer::GL::RenderLayerGL::Submit(RenderComponent& a_renderable, TransformComponent& a_trans)
{
    Renderable* r = new Renderable();
    r->m_renderComponent = &a_renderable;
    r->m_modelMatrix = a_trans.GetTransform();

    r->m_modelMatrix.m_00 = a_trans.GetUniformedScale();
    r->m_modelMatrix.m_11 = a_trans.GetUniformedScale();
    r->m_modelMatrix.m_22 = a_trans.GetUniformedScale();

    m_renderables.push_back(r);
}

void Me::Renderer::GL::RenderLayerGL::SetCamera(CameraComponent& a_cameraComp, TransformComponent& a_transComp)
{
    Math::Mat4 camMat = Math::Mat4::Identity();

    if(a_cameraComp.m_cameraType == Me::CameraType::Orthographic)
    {
        camMat = Math::GetOrthographicMatrix(-a_cameraComp.m_size.m_y / 2, a_cameraComp.m_size.m_y / 2,
            -a_cameraComp.m_size.m_x / 2 , a_cameraComp.m_size.m_x / 2,
            a_cameraComp.m_near, a_cameraComp.m_far);
    }
    else
    {
        camMat = Math::GetProjectionMatrix((45.0f*(3.14f/180.0f)), a_cameraComp.m_near, a_cameraComp.m_far);
    }
    
    Math::Mat4 trans = a_transComp.GetTransform();
    Math::Mat4 camViewProjection = trans * camMat;
    
    m_cameraMat = &camViewProjection;
}

Me::Resources::GL::Mesh* Me::Renderer::GL::RenderLayerGL::CreateMesh(std::vector<Vertex> a_vertices, std::vector<uint16_t> a_indices)
{
    return new Resources::GL::Mesh(a_vertices, a_indices);
}