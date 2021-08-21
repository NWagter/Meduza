#pragma once

namespace Me
{
    namespace Helper
    {
        namespace GL
        {
            struct ShaderSources
            {
                std::string m_vertexSource;
                std::string m_pixelSource;
                std::string m_shaderName;
            };

            class ShaderHelper
            {
            public:
                static ShaderSources GetSources(std::string, std::string);
                static ShaderSources GetSources(std::string);
            };
        }
    }
}