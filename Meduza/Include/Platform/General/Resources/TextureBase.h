#pragma once
namespace Me
{
    namespace Resources
    {
        class TextureBase
        {
        public:
            TextureBase(const Math::Vec2);

            virtual ~TextureBase();   

            virtual void Reload() = 0;
            virtual void Unload() = 0;

            inline Math::Vec2 GetSize() const {return m_size;}

        protected:
            Math::Vec2 m_size;
        };
    }
}