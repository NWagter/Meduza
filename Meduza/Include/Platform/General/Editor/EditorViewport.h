#pragma once

#include "Platform/General/Editor/EditorWidget.h"

namespace Me
{

    namespace Renderer
    {
        class RenderLayer;
    }

    namespace Editor
    {
        class EntityEditor;
        class EditorToolbar;

        class EditorViewport : public EditorWidget
        {
            public:
                EditorViewport(EntityEditor& a_editor, EditorToolbar& a_toolbar, Renderer::RenderLayer& a_renderLayer);
                ~EditorViewport();

                void Draw() override;

            private:
                EntityEditor* m_editor;
                EditorToolbar* m_toolbar;
                Renderer::RenderLayer* m_renderLayer;
                EntityID m_editorCamera;

                Math::Vec2 m_viewportSize = { 0.0f, 0.0f };
        };
    }
}