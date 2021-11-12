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
                static EditorRenderer* CreateEditor(Renderer::RenderLayer*);
                virtual ~EditorRenderer();

                virtual void Clear() = 0;
                virtual void Update(float) = 0;
                virtual void Populate() = 0;

                void AddWidget(EditorWidget* const);

            protected:
                std::vector<EditorWidget*> m_editorWidgets;
        };
    }
}