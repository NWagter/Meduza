#pragma once

namespace Me
{
    namespace Resources
    {
        class TextureBase;

        class TextureLibrary
        {
        public:
            static TextureLibrary* CreateTextureLibrary();
            static void Destroy();

            static Texture CreateTexture(std::string);
            
            static TextureBase* GetTexture(std::string);
            static TextureBase* GetTexture(unsigned int);

            static bool UnloadTexture(std::string);
            static bool UnloadTexture(unsigned int, bool = true);

        private:
            TextureLibrary();
            ~TextureLibrary();

            static TextureLibrary* ms_instance;
            std::unordered_map<Texture, TextureBase*> m_textures;            
        };
        
    }
    
}
