#pragma once

#include "Platform/General/Resources/ShaderBase.h"
#include "Platform/Linux/Helper/ShaderReader.h"

namespace Me
{
    namespace Resources
    {
        namespace GL
        {
            class Shader : public ShaderBase
            {
            public:
                Shader(std::string, std::string);
                Shader(std::string);

                virtual ~Shader();   

                void Reload() override;
                void Unload() override;

                void Bind() override;
                void UnBind() override;

            private:
                Helper::GL::ShaderSources m_source;
            
                unsigned int GenerateShader();
                unsigned int m_program;
            };
        }
    }
}