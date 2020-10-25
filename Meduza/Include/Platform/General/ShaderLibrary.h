#pragma once
namespace Me
{
    namespace Renderer
    {
        class RenderLayer;
    }

    namespace Resources
    {
        class ShaderBase;

        class ShaderLibrary
        {
        public:
            static ShaderLibrary* CreateShaderLibrary(Renderer::RenderLayer&);
            static void Destroy();

            static ShaderBase* CreateShader(std::string);
            static ShaderBase* CreateShader(std::string, std::string);
            
            static ShaderBase* GetShader(std::string);
            static ShaderBase* GetShader(unsigned int);

            static bool UnLoadShader(std::string);
            static bool UnLoadShader(unsigned int, bool = true);

        private:
            ShaderLibrary(Renderer::RenderLayer&);
            ~ShaderLibrary();
            
            Renderer::RenderLayer* m_renderLayer;

            static ShaderLibrary* ms_instance;
            std::unordered_map<unsigned int, ShaderBase*> m_shaders;
        };
    }
}