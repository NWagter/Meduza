#pragma once

namespace Me
{
    namespace Renderer
    {
        class ContextBase;

        struct FrameBufferSpecs
        {
            GFX_API m_api;
            Math::Vec2 m_size;
            uint16_t m_samples;

            bool m_swapchainTarget = false;
        };

        class FrameBuffer
        {
        public:
            static FrameBuffer* Create(const FrameBufferSpecs&, ContextBase& a_context);

            virtual const FrameBufferSpecs& GetFrameBufferSpec() const = 0;
            virtual unsigned int GetColourAttachment() = 0;

            virtual void Resize(Math::Vec2) = 0;
            virtual void Bind() = 0;
            virtual void UnBind() = 0;
        protected:
            ContextBase* m_context;
        };
    }
}