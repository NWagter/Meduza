#pragma once

namespace Me
{
    namespace Editor
    {
        class EditorWidget
        {
            public:
                EditorWidget();
                ~EditorWidget();

                virtual void Draw() = 0;
        };
    }
}