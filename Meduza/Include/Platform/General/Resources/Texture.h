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
                    Texture(std::string, const std::vector<unsigned char>, int, int);
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