#pragma once

#include "Platform/General/Resources/Resource.h"

namespace Me
{
    namespace Resources
    {

        enum class ShaderType
        {
            VertexShader,
            FragmentShader
        };

        class ShaderBase : public ResourceBase
        {
        public:
            ShaderBase() : ResourceBase(ResourceType::Shader) {};
            virtual ~ShaderBase();   

            virtual void Load() {};
            virtual void Reload() {};
            virtual void Unload() {};

            virtual void Bind() {};
            virtual void UnBind() {};

            ShaderBase* OnCreate(const std::string& a_path) override;
            void OnLoad() override { Load(); }
        protected:

        };
    }
}