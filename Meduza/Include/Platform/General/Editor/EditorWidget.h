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

                virtual void Update(float a_dt);
                virtual void Draw() = 0;
        };
    }
}