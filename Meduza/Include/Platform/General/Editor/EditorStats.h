#pragma once

#include "Platform/General/Editor/EditorWidget.h"

namespace Me
{
    namespace Renderer
    {
        class RenderLayer;
    }

    namespace Editor
    {
        class EditorStats : public EditorWidget
        {
        public:
            EditorStats(Renderer::RenderLayer&);
            ~EditorStats();

            void Update(float) override;
            void Draw() override;

        private:
            Renderer::RenderLayer* m_renderLayer;
            float m_deltaTime;
            int m_frames;
            bool m_open;
        };
    }
}