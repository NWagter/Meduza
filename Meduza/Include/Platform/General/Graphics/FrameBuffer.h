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

        struct ColourAttachment
        {
            GFX_API m_api;            
        };

        class FrameBuffer
        {
        public:
            static FrameBuffer* Create(FrameBufferSpecs const& a_spec, ContextBase& a_context);
            virtual ~FrameBuffer() = default;

            virtual const FrameBufferSpecs& GetFrameBufferSpec() const = 0;
            virtual ColourAttachment* GetColourAttachment() = 0;

            virtual void Resize(Math::Vec2 const& a_size) = 0;
            virtual void Bind() { };
            virtual void UnBind() { };
        protected:
            ContextBase* m_context;
        };
    }
}