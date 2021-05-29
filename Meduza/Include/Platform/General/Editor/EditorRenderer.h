#pragma once

namespace Me
{
    namespace Renderer
    {
        class RenderLayer;
    }

    namespace Editor
    {
        class EditorRenderer
        {
            public:
                static EditorRenderer* CreateEditor(Renderer::RenderLayer*);

                virtual void Clear() = 0;
                virtual void Populate() = 0;
        };
    }
}