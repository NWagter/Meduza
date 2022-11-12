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

                    void Load() override;
                    void Reload() override;
                    void Unload() override;

                    void Bind(int);
                    void UnBind(int);

                    unsigned int GetTexture() { return m_texture; }
                private:
                    unsigned int m_texture; 
                    std::vector<unsigned char> m_textureData;

                    void LoadFromFile();
                    void LoadFromData();
                };
            }
    }
}