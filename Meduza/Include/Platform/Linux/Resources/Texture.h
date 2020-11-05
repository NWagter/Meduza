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
                    ~Texture();

                    virtual void Reload();
                    virtual void Unload();

                    void Bind();
                    void UnBind();
                private:
                    unsigned int m_texture;
                };
            }
    }
}