#pragma once
namespace Me
{
    namespace Resources
    {
        class TextureBase
        {
        public:
            TextureBase();

            virtual ~TextureBase();   

            virtual void Reload() = 0;
            virtual void Unload() = 0;

            virtual void Bind() = 0;
            virtual void UnBind() = 0;

        protected:

        };
    }
}