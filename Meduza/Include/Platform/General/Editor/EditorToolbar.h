#pragma once

#include "Platform/General/Editor/EditorWidget.h"

namespace Me
{
    namespace Editor
    {

        class EditorToolbar : public EditorWidget
        {
            public:
                EditorToolbar();
                ~EditorToolbar();

                void Draw() override;

            private:

        };
    }
}