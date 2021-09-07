#pragma once

#include "Platform/General/Editor/EditorWidget.h"

namespace Me
{
    class Window;

    namespace Editor
    {

        class EditorToolbar : public EditorWidget
        {
            public:
                EditorToolbar(Window&);
                ~EditorToolbar();

                void Draw() override;

            private:
                Window* m_window;

        };
    }
}