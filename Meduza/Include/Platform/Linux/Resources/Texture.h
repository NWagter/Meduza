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
                    Texture(std::string);
                    Texture(const std::vector<unsigned char>, int, int);
                    virtual ~Texture();

                    void Reload() override;
                    void Unload() override;

                    void Bind();
                    void UnBind();
                private:
                    unsigned int m_texture;
                };
            }
    }
}