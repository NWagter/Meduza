#pragma once

#include "Platform/General/Editor/EditorWidget.h"

namespace Me
{
    class Window;
    enum class CameraType : int;

    namespace Editor
    {
        class EditorProjectManager;

        class EditorToolbar : public EditorWidget
        {
            public:
                EditorToolbar(Window& a_window, EditorProjectManager& a_projectManager);
                ~EditorToolbar();

                void Draw() override;

                ImGuizmo::OPERATION GetOperationType() const { return m_currentOperationType;}
            private:
                Window* m_window;
                EditorProjectManager* m_projectManager;
                CameraType m_activeCameraType;
                ImGuizmo::OPERATION m_currentOperationType;

        };
    }
}