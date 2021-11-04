#include "MePCH.h"
#include "Platform/General/Editor/EditorViewport.h"

#include "MeduzaIncluder.h"

#include "Platform/General/Editor/EditorEntityEditor.h"
#include "Platform/General/Editor/EditorToolbar.h"

#include "Platform/General/Graphics/RenderLayer.h"
#include "Platform/General/Window.h"

#include "Platform/General/Graphics/FramebufferGL.h"
#include "Platform/Windows/Graphics/FramebufferDx12.h"

Me::Editor::EditorViewport::EditorViewport(EntityEditor& a_editor, EditorToolbar& a_toolbar, Renderer::RenderLayer& a_renderer)
{
    m_renderLayer = &a_renderer;
    m_editor = &a_editor;
    m_toolbar = &a_toolbar;

    m_editorCamera = 0;
}

Me::Editor::EditorViewport::~EditorViewport()
{

}

void Me::Editor::EditorViewport::Draw()
{
	auto frameBuffer = m_renderLayer->GetFrameBuffer();

    if(frameBuffer->GetColourAttachment()->m_api == GFX_API::DX12)
    return;

	ImGui::Begin("Viewport");

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	Math::Vec2 panelSize = Math::Vec2(viewportPanelSize.x, viewportPanelSize.y);
	if(m_viewportSize != panelSize)
	{
		frameBuffer->Resize(Math::Vec2(viewportPanelSize.x, viewportPanelSize.y));
	}
	m_viewportSize = panelSize;
    auto colourAttachment = frameBuffer->GetColourAttachment();

    switch (colourAttachment->m_api)
    {
    case GFX_API::DX12:
        D3D12_GPU_DESCRIPTOR_HANDLE handle = static_cast<Renderer::ColourAttachmentDx12*>(colourAttachment)->m_texture;
        if(handle.ptr != 0)
        {
            ImGui::Image(
                (ImTextureID)handle.ptr, 
                ImVec2{ m_viewportSize.m_x, m_viewportSize.m_y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
        }
        break;
    case GFX_API::OpenGL:
	    ImGui::Image(
            (ImTextureID)static_cast<Renderer::ColourAttachmentGL*>(colourAttachment)->m_texture, 
            ImVec2{ m_viewportSize.m_x, m_viewportSize.m_y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });   
    default:
        break;
    }


    if(m_editorCamera <= 0)
    {               
        auto eManager = EntityManager::GetEntityManager();
        EntityFilter filter;
        filter.insert(CameraComponent::s_componentID);
        filter.insert(EditorComponent::s_componentID);

        auto ents = eManager->GetEntities(filter);

        if(ents.size() > 0)
        {
            m_editorCamera = ents.at(0);
        }
    }

    auto eManager = EntityManager::GetEntityManager();

    auto editorCam = eManager->GetComponent<CameraComponent>(m_editorCamera);
    if(editorCam != nullptr)
    {

        auto camTrans = eManager->GetComponent<TransformComponent>(m_editorCamera);
        Math::Mat4 rMat = Math::Mat4::Identity();
        rMat.Rotation(camTrans->m_rotation);

        Math::Mat4 pMat = Math::Mat4::Identity();
        pMat.SetPosition(camTrans->m_translation);

        Math::Mat4 view = rMat * pMat.Inverse();
        Math::Mat4 projection;
        Math::Vec2 size = m_renderLayer->GetWindow()->GetSize();
        float aspect = size.m_x / size.m_y;
        
        switch (editorCam->m_cameraType)
        {
        case CameraType::Orthographic:
            ImGuizmo::SetOrthographic(true);
            projection = Math::GetOrthographicMatrix(-editorCam->m_orthoScale, editorCam->m_orthoScale,
                            -editorCam->m_orthoScale * aspect , editorCam->m_orthoScale * aspect,
                            editorCam->m_near, editorCam->m_far);
            break;
        case CameraType::Perspective:
            ImGuizmo::SetOrthographic(false);
            projection = Math::GetProjectionMatrix(45.0f, editorCam->m_size.m_x / editorCam->m_size.m_y,
                                    editorCam->m_near, editorCam->m_far);
            break;
        }

        ImGuizmo::SetDrawlist();
        ImGuizmo::SetRect(ImGui::GetWindowPos().x,ImGui::GetWindowPos().y, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);

        auto trans = eManager->GetComponent<TransformComponent>(m_editor->GetSelectedId());
        if(trans != nullptr)
        {
            Math::Mat4 t =  Math::Transpose(trans->GetTransform());
            ImGuizmo::Manipulate(Math::Transpose(view).m_m, Math::Transpose(projection).m_m,
            m_toolbar->GetOperationType(), ImGuizmo::LOCAL, t.m_m);

            if(ImGuizmo::IsUsing())
            {
                t =  Math::Transpose(t);
                trans->m_translation = t.GetPosition();
            }
        }

    }




	ImGui::End();
}