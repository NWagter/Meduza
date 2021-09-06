#pragma once
namespace Me
{
    namespace Resources
    {

        enum class ShaderType
        {
            VertexShader,
            FragmentShader
        };

        class ShaderBase
        {
        public:
            ShaderBase(std::string);

            virtual ~ShaderBase();   

            virtual void Reload() = 0;
            virtual void Unload() = 0;

            virtual void Bind() = 0;
            virtual void UnBind() = 0;

            inline std::string GetPath() const { return m_shaderPath;}
        protected:

            std::string m_shaderPath;

        };
    }
}