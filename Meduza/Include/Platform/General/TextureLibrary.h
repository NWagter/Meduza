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

            static Texture CreateTexture(std::string);
            static Texture CreateTexture(const std::vector<unsigned char>, int, int, std::string, std::string);
            
            static Texture GetTexture(std::string);
            static TextureBase* GetTexture(Texture);

            static bool UnloadTexture(std::string);
            static bool UnloadTexture(Texture, bool = true);

        private:
            TextureLibrary(Renderer::RenderLayer& a_renderLayer);
            ~TextureLibrary();
            
            Renderer::RenderLayer* m_renderLayer;

            static TextureLibrary* ms_instance;
            std::unordered_map<Texture, TextureBase*> m_textures;            
        };
        
    }
    
}
