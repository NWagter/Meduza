#pragma once

#include "Platform/General/Editor/EditorWidget.h"

namespace Me
{
    using EntityID = uint64_t;

    namespace Editor
    {
        class EntityHierarchy;

        class EntityEditor : public EditorWidget
        {
            public:
                EntityEditor(EntityHierarchy& a_entityHierarchy);
                ~EntityEditor();

                void Draw() override;

                EntityID GetSelectedId() const {return m_selectedEntity;}
            private:
                EntityHierarchy* m_hierarchy;
                EntityID m_selectedEntity;

                bool m_locked = false;

        };
    }
}