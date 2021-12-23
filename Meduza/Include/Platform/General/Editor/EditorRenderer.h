#pragma once

namespace Me
{
    namespace Renderer
    {
        class RenderLayer;
    }

    namespace Editor
    {
        class EditorWidget;

        class EditorRenderer
        {
            public:
                static EditorRenderer* CreateEditor(Renderer::RenderLayer* a_renderLayer);
                virtual ~EditorRenderer();

                virtual void Clear() = 0;
                virtual void Update(float a_dt) = 0;
                virtual void Populate() = 0;

                void AddWidget(EditorWidget* const a_widgest);

            protected:
                std::vector<EditorWidget*> m_editorWidgets;
        };
    }
}