#pragma once

#include "Platform/General/Editor/EditorWidget.h"

namespace Me
{
    using EntityID = uint64_t;

    namespace Renderer
    {
        namespace GL
        {
            class RenderLayerGL;
        }
    }

    namespace Editor
    {
        class EntityEditor;
        class EditorToolbar;

        class EditorViewport : public EditorWidget
        {
            public:
                EditorViewport(EntityEditor&, EditorToolbar&, Renderer::GL::RenderLayerGL&);
                ~EditorViewport();

                void Draw() override;

            private:
                EntityEditor* m_editor;
                EditorToolbar* m_toolbar;
                Renderer::GL::RenderLayerGL* m_renderLayer;
                EntityID m_editorCamera;

                Math::Vec2 m_viewportSize = { 0.0f, 0.0f };

                bool m_locked = false;

        };
    }
}