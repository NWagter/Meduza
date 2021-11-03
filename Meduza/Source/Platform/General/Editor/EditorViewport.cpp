#include "MePCH.h"
#include "Platform/General/Editor/EditorViewport.h"

#include "MeduzaIncluder.h"

#include "Platform/General/Editor/EditorEntityEditor.h"
#include "Platform/General/Editor/EditorToolbar.h"

#include "Platform/General/Graphics/RenderLayerGL.h"
#include "Platform/General/Window.h"

#include "Platform/General/Graphics/FrameBuffer.h"

Me::Editor::EditorViewport::EditorViewport(EntityEditor& a_editor, EditorToolbar& a_toolbar, Renderer::GL::RenderLayerGL& a_renderer)
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
	ImGui::Begin("Viewport");

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	auto frameBuffer = m_renderLayer->GetFrameBuffer();
	Math::Vec2 panelSize = Math::Vec2(viewportPanelSize.x, viewportPanelSize.y);
	if(m_viewportSize != panelSize)
	{
		frameBuffer->Resize(Math::Vec2(viewportPanelSize.x, viewportPanelSize.y));
	}
	m_viewportSize = panelSize;
	unsigned int texture = frameBuffer->GetColourAttachment();
	ImGui::Image(reinterpret_cast<void*>(texture), ImVec2{ m_viewportSize.m_x, m_viewportSize.m_y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });


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