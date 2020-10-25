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
            ShaderBase();

            virtual ~ShaderBase();   

            virtual void Reload() = 0;
            virtual void Unload() = 0;

            virtual void Bind() = 0;
            virtual void UnBind() = 0;

        protected:

        };
    }
}