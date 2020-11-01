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

            static Shader CreateShader(std::string);
            static Shader CreateShader(std::string, std::string);
            
            static ShaderBase* GetShader(std::string);
            static ShaderBase* GetShader(Shader);

            static bool UnLoadShader(std::string);
            static bool UnLoadShader(Shader, bool = true);

        private:
            ShaderLibrary(Renderer::RenderLayer&);
            ~ShaderLibrary();
            
            Renderer::RenderLayer* m_renderLayer;

            static ShaderLibrary* ms_instance;
            std::unordered_map<Shader, ShaderBase*> m_shaders;
        };
    }
}