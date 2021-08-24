#pragma once

#include "Platform/General/Editor/EditorWidget.h"

namespace Me
{
    using EntityID = uint64_t;

    namespace Editor
    {
        class EntityHierarchy : public EditorWidget
        {
            public:
                EntityHierarchy();
                ~EntityHierarchy();

                void Draw() override;

            private:
                EntityID m_selectedEntity;
        };
    }
}