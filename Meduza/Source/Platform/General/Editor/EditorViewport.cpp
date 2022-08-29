#include "MePCH.h"
#include "Platform/General/Editor/EditorViewport.h"

#include "MeduzaIncluder.h"

#include "Platform/General/Editor/EditorEntityEditor.h"
#include "Platform/General/Editor/EditorToolbar.h"

#include "Platform/General/Graphics/RenderLayer.h"
#include "Platform/General/Window.h"

#include "Platform/General/Graphics/FramebufferGL.h"

#include "Platform/General/Resources/Resource.h"
#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/Helper/Helper.h"
#endif

#include "Core/Meduza.h"

Me::Editor::EditorViewport::EditorViewport(EntityEditor& a_editor, EditorToolbar& a_toolbar, Renderer::RenderLayer& a_renderLayer)
{
    m_renderLayer = &a_renderLayer;
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

	ImGui::Begin("Viewport");
    Me::Event::EventSystem::GetEventSystem()->SetViewportFocus(ImGui::IsWindowFocused());

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	Math::Vector2 panelSize = Math::Vector2(viewportPanelSize.x, viewportPanelSize.y);
	if(m_viewportSize != panelSize)
	{
		frameBuffer->Resize(panelSize);
        Me::Event::EventSystem::GetEventSystem()->SetViewportSize(panelSize);
	}
	m_viewportSize = panelSize;
    auto colourAttachment = frameBuffer->GetColourAttachment();

    switch (colourAttachment->m_api)
    {
    case GFX_API::DX12:
    {
        ME_CORE_ASSERT_M(false, "No implementation yet for DX12");
        break;
    }
    case GFX_API::OpenGL:
	    ImGui::Image(
            reinterpret_cast<void*>(static_cast<Renderer::ColourAttachmentGL*>(colourAttachment)->m_texture), 
            ImVec2{ m_viewportSize.m_x, m_viewportSize.m_y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });   
    default:
        break;
    }

    if (ImGui::BeginDragDropTarget())
    {
        if (ImGuiPayload const* payLoad = ImGui::AcceptDragDropPayload("ASSET_ITEM"))
        {
            Files::MeduzaFile* file = (Files::MeduzaFile*)(payLoad->Data);

            if (file->m_type == Resources::ResourceType::Scene)
            {
                Meduza::ms_engineState = RUN_EDITOR;
                Serialization::Serializer::GetInstance()->DeserializeScene(file->m_path);
            }
            else if (file->m_type == Resources::ResourceType::Prefab)
            {
                Serialization::Serializer::GetInstance()->DeserializeEntity(file->m_path);
            }
        }
        
        ImGui::EndDragDropTarget();
    }


    if(m_editorCamera <= 0)
    {               
        auto const eManager = EntityManager::GetEntityManager();
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
        Math::Matrix4 rMat = Math::Matrix4::Identity();
        rMat.Rotation(camTrans->m_rotation);

        Math::Matrix4 pMat = Math::Matrix4::Identity();
        pMat.SetPosition(camTrans->m_translation);

        Math::Matrix4 view = Math::Transpose(rMat * pMat.Inverse());
        Math::Matrix4 projection;
        Math::Vector2 size = m_renderLayer->GetWindow()->GetSize();
        float aspect = size.m_x / size.m_y;
        
        switch (editorCam->m_cameraType)
        {
        case CameraType::Orthographic:

            ImGuizmo::SetOrthographic(true);
            projection = Math::Transpose(Math::GetOrthographicMatrix(-editorCam->m_orthoScale, editorCam->m_orthoScale,
                            -editorCam->m_orthoScale * aspect , editorCam->m_orthoScale * aspect,
                            editorCam->m_near, editorCam->m_far));
            break;
        case CameraType::Perspective:

            ImGuizmo::SetOrthographic(false);
            projection = Math::Transpose(Math::GetProjectionMatrix(45.0f, editorCam->m_size.m_x / editorCam->m_size.m_y,
                                    editorCam->m_near, editorCam->m_far));
            break;
        }

        ImGuizmo::SetDrawlist();
        ImGuizmo::SetRect(ImGui::GetWindowPos().x,ImGui::GetWindowPos().y, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);

        auto trans = eManager->GetComponent<TransformComponent>(m_editor->GetSelectedId());
        if(trans != nullptr)
        {
            Math::Matrix4 t =  Math::Transpose(trans->GetTransform());
            ImGuizmo::Manipulate(view.m_m, projection.m_m,
            m_toolbar->GetOperationType(), ImGuizmo::WORLD, t.m_m);

            if(ImGuizmo::IsUsing())
            {
                float matrixTranslation[3], matrixRotation[3], matrixScale[3];
                ImGuizmo::DecomposeMatrixToComponents(t.m_m, matrixTranslation, matrixRotation, matrixScale);

                Math::Vector3 deltaTrans = Math::Vector3(matrixTranslation[0], matrixTranslation[1], matrixTranslation[2]) - trans->m_translation;
                trans->m_translation += deltaTrans;

                Math::Vector3 deltaRot = Math::Vector3(std::abs(matrixRotation[0]), std::abs(matrixRotation[1]), std::abs(matrixRotation[2])) - trans->m_rotation;
                trans->m_rotation += deltaRot;

                Math::Vector3 deltaScale = Math::Vector3(matrixScale[0], matrixScale[1], matrixScale[2]) - trans->m_scale;
                trans->m_scale += deltaScale;
            }
        }

    }




	ImGui::End();
}