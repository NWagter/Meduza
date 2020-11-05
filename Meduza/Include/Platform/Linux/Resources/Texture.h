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