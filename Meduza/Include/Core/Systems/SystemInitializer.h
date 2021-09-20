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
        SystemInitializer(Me::Renderer::RenderLayer&);
        ~SystemInitializer();

    private:
        std::vector<ECSSystem*> m_systems;
    };
    
}