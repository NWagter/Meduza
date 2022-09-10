#pragma once

#include "FrameBuffer.h"

namespace Me
{
    namespace Renderer
    {
        struct ColourAttachmentGL : public ColourAttachment
        {
            uint64_t m_texture;   
        };

        namespace GL
        {          
            class FrameBufferGL : public FrameBuffer
            {
            public:
                FrameBufferGL(FrameBufferSpecs const& a_spec, ContextBase& a_context);
                ~FrameBufferGL();

                void Create();
                void Resize(Math::Vector2 const& a_size) override;
                void Bind() override;
                void UnBind() override;

                inline const FrameBufferSpecs& GetFrameBufferSpec() const override
                {
                    return m_spec;
                };
                ColourAttachment* GetColourAttachment() override;

            private:
                unsigned int m_renderTextureID;
                unsigned int m_colourAttachment;
                unsigned int m_depthAttachment;
                FrameBufferSpecs m_spec;
                ColourAttachmentGL* m_attachment;
            };  
        }         
    }
}