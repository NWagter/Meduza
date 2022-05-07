#pragma once

#include "Platform/General/Resources/Resource.h"

namespace Me
{
    namespace Resources
    {
        class TextureBase : public ResourceBase
        {
        public:            
            TextureBase() : ResourceBase(ResourceType::Texture) {};
            TextureBase(Math::Vector2 const& a_size);

            virtual ~TextureBase();   

            virtual void Reload() {};
            virtual void Unload() {};

            inline Math::Vector2 GetSize() const {return m_size;}

            TextureBase* OnCreate(const std::string& a_path) override;
            TextureBase* Create(std::vector<unsigned char> const& a_texture, int const a_width, int const a_height);
        protected:
            Math::Vector2 m_size;
        };
    }
}