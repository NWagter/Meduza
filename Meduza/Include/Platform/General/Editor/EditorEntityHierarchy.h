#pragma once

#include "Platform/General/Editor/EditorWidget.h"

namespace Me
{
    class Window;
    using EntityID = uint64_t;

    namespace Editor
    {
        class EntityHierarchy : public EditorWidget
        {
            public:
                EntityHierarchy(Window& a_window);
                ~EntityHierarchy();

                void Draw() override;


                EntityID GetSelected();
            private:
                EntityID m_selectedEntity;
                Window* m_window;
        };
    }
}