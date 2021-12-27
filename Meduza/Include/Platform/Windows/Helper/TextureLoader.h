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
                TextureLoader(Renderer::Dx12::Device& a_device, Renderer::Dx12::CommandList& a_cmd, Renderer::Dx12::Descriptor& a_srv);
                ~TextureLoader();

                const TextureReturnData* LoadTexture(std::string const& a_file);
                const TextureReturnData* LoadTexture(std::vector<unsigned char> const& a_texture, int const a_width, int const a_height);

                inline SRV GetSRV(unsigned int const a_index) {return m_srvs.at(a_index);}
            private:
                TextureData* CreateTexture(std::string const& a_file, std::string const& a_ext);
                SRV SRVOffset(unsigned int* a_srv, TextureData& a_texture);
                SRV LoadToSRV(TextureData& a_texture, unsigned int a_index);

                Renderer::Dx12::Device* m_device;
                Renderer::Dx12::CommandList* m_cmd;

                std::vector<SRV> m_srvs;
                unsigned int m_currentID;              
            };
        }
    }
}