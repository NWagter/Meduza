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
                Shader(std::string a_vertexShader, std::string a_pixelShader);
                Shader(std::string a_shader);

                virtual ~Shader();   

                void Reload() override;
                void Unload() override;

                void Bind() override;
                void UnBind() override;

                void SetFloat(std::string const& a_location, float const a_value);
                void SetVec3(std::string const& a_location, Math::Vec3 const& a_vec3);
                void SetVec4(std::string const& a_location, Math::Vec4 const& a_vec4);
                void SetMat4(std::string const& a_location, Math::Mat4 const& a_mat4, bool const a_transpose);

            private:
                Helper::GL::ShaderSources m_source;
            
                unsigned int GenerateShader();
                unsigned int m_program;
            };
        }
    }
}