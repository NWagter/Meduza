#pragma once

#include "Platform/General/Resources/TextureBase.h"

namespace Me
{   
    namespace Helper
    {
        namespace Dx12
        {
            struct TextureData;
        }
    }

    namespace Resources
    {
        namespace Dx12
            {
                class Texture : public TextureBase
                {
                public:
                    Texture(unsigned int, Helper::Dx12::TextureData&, const Math::Vec2);
                    ~Texture();

                    virtual void Reload();
                    virtual void Unload();

                    inline Helper::Dx12::TextureData& GetTexture() {return *m_texture;}
                    inline unsigned int GetSRVId() const {return m_srvId;}
                private:
                    unsigned int m_srvId;
                    Helper::Dx12::TextureData* m_texture;
                };
            }
    }
}