#pragma once

namespace Me
{
    namespace Renderer
    {
        namespace Dx12
        {
            class Device;
            class CommandList;
            class Descriptor;
        }
    }


    namespace Helper
    {
        namespace Dx12
        {
            struct TextureData;
            
            struct SRV
            {
                Renderer::Dx12::Descriptor* m_srv;
                std::vector<TextureData*> m_textures;
            };

            struct TextureReturnData
            {
                TextureData* m_textureData = nullptr;
                Math::Vec2 m_size;
                unsigned int m_srvId;
            };

            class TextureLoader
            {
            public:
                TextureLoader(Renderer::Dx12::Device&, Renderer::Dx12::CommandList&);
                ~TextureLoader();

                const TextureReturnData* LoadTexture(std::string);
                const TextureReturnData* LoadTexture(const std::vector<unsigned char>, int, int);

                inline SRV GetSRV(unsigned int a_id) {return m_srvs.at(a_id);}
            private:
                TextureData* CreateTexture(std::string, std::string);
                void SRVOffset(unsigned int*, TextureData&);
                void LoadToSRV(TextureData&, unsigned int);

                Renderer::Dx12::Device* m_device;
                Renderer::Dx12::CommandList* m_cmd;

                std::vector<SRV> m_srvs;
                unsigned int m_currentID;              
            };
        }
    }
}