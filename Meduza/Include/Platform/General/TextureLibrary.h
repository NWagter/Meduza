#pragma once

namespace Me
{
    namespace Renderer
    {
        class RenderLayer;
    }

    namespace Resources
    {
        class TextureBase;

        class TextureLibrary
        {
        public:
            static TextureLibrary* CreateTextureLibrary(Renderer::RenderLayer& a_renderLayer);
            static void Destroy();

            static Texture CreateTexture(std::string const& a_texture);
            static Texture CreateTexture(std::vector<unsigned char> const& a_texture, int const a_width, int const a_height, std::string const& a_name, std::string const& a_file);
            
            static Texture GetTexture(std::string const& a_texture);
            static TextureBase* GetTexture(Texture const a_texture);

            static bool UnloadTexture(std::string const& a_texture);
            static bool UnloadTexture(Texture const a_texture, bool const a_message = true);

        private:
            TextureLibrary(Renderer::RenderLayer& a_renderLayer);
            ~TextureLibrary();
            
            Renderer::RenderLayer* m_renderLayer;

            static TextureLibrary* ms_instance;
            std::unordered_map<Texture, TextureBase*> m_textures;            
        };
        
    }
    
}
