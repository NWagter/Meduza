#pragma once

#include "Platform/General/Graphics/FrameBuffer.h"

namespace Me
{
    namespace Renderer
    {

        struct ColourAttachmentDx12 : public ColourAttachment
        {
            D3D12_GPU_DESCRIPTOR_HANDLE m_texture;          
        };

        namespace Dx12
        {          
            class FrameBufferDx12 : public FrameBuffer
            {
            public:
                FrameBufferDx12(const FrameBufferSpecs&, ContextBase&);
                ~FrameBufferDx12();

                void Resize(Math::Vec2) override;

                inline const FrameBufferSpecs& GetFrameBufferSpec() const override
                {
                    return m_spec;
                };
                ColourAttachment* GetColourAttachment() override;
            private:
                FrameBufferSpecs m_spec;
                ColourAttachmentDx12* m_attachment;
            };  
        }         
    }
}