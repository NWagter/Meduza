#pragma once
namespace Me
{
    namespace Resources
    {
        class TextureBase
        {
        public:
            TextureBase(const Math::Vec2, std::string);

            virtual ~TextureBase();   

            virtual void Reload() = 0;
            virtual void Unload() = 0;

            inline Math::Vec2 GetSize() const {return m_size;}
            inline std::string GetPath() const {return m_filePath;}
        protected:
            Math::Vec2 m_size;
            std::string m_filePath;
        };
    }
}