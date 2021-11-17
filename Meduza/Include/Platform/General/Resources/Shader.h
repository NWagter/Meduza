#pragma once

#include "Platform/General/Resources/ShaderBase.h"
#include "Platform/General/Helper/ShaderReader.h"

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

                void SetFloat(const std::string&, const float);
                void SetVec3(const std::string &, const Math::Vec3);
                void SetVec4(const std::string &, const Math::Vec4);
                void SetMat4(const std::string &a_name, const Math::Mat4, const bool);

            private:
                Helper::GL::ShaderSources m_source;
            
                unsigned int GenerateShader();
                unsigned int m_program;
            };
        }
    }
}