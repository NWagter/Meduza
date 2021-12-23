#pragma once

#include "Platform/General/Resources/TextureBase.h"

namespace Me
{   
    namespace Resources
    {
        namespace GL
            {
                class Texture : public TextureBase
                {
                public:
                    Texture(std::string const& a_file);
                    Texture(std::vector<unsigned char> const& a_texture, int const a_width, int const a_height);
                    virtual ~Texture();

                    void Reload() override;
                    void Unload() override;

                    void Bind(int);
                    void UnBind(int);
                private:
                    unsigned int m_texture;
                };
            }
    }
}