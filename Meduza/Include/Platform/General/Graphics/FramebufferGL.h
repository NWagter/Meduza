#pragma once

#include "FrameBuffer.h"

namespace Me
{
    namespace Renderer
    {
        namespace GL
        {          
            class FrameBufferGL : public FrameBuffer
            {
            public:
                FrameBufferGL(const FrameBufferSpecs&, ContextBase&);
                ~FrameBufferGL();

                void Create();
                void Resize(Math::Vec2) override;
                void Bind() override;
                void UnBind() override;

                inline const FrameBufferSpecs& GetFrameBufferSpec() const override
                {
                    return m_spec;
                };
                inline unsigned int GetColourAttachment() override
                { 
                    return m_colourAttachment;
                }
            private:
                unsigned int m_renderTextureID;
                unsigned int m_colourAttachment;
                unsigned int m_depthAttachment;
                FrameBufferSpecs m_spec;
            };  
        }         
    }
}