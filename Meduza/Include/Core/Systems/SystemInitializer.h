#pragma once

namespace Me
{
    class ECSSystem;

    namespace Renderer
    {
        class RenderLayer;
    }
    class SystemInitializer
    {
    public:
        SystemInitializer(Me::Renderer::RenderLayer& a_renderLayer);
        ~SystemInitializer();

    private:
        void PrintComponentsSize();
        std::vector<ECSSystem*> m_systems;
    };
    
}