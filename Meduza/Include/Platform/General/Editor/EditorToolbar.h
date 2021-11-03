#pragma once

#include "Platform/General/Editor/EditorWidget.h"

namespace Me
{
    class Window;
    enum class CameraType : int;

    namespace Editor
    {

        class EditorToolbar : public EditorWidget
        {
            public:
                EditorToolbar(Window&);
                ~EditorToolbar();

                void Draw() override;

                ImGuizmo::OPERATION GetOperationType() const { return m_currentOperationType;}
            private:
                Window* m_window;
                CameraType m_activeCameraType;
                ImGuizmo::OPERATION m_currentOperationType;

        };
    }
}