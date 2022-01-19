#pragma once

#include "Platform/General/Editor/EditorWidget.h"

namespace Me
{
    namespace Editor
    {
        class EditorScriptConfig : public EditorWidget
        {
        public:
            EditorScriptConfig();
            ~EditorScriptConfig();

            void Update(float a_dt) override;
            void Draw() override;

        private:

        };
    }
}