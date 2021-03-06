#pragma once
#include "Platform/General/Graphics/RenderLayer.h"
#include "Platform/Windows/Helper/BufferStructures.h"

namespace Me 
{
    class WindowsWindow;

    namespace Resources
    {
        namespace Dx12
        {
            class Mesh;
            class Shader;
            class Texture;
        }
    }

    namespace Helper
    {
        namespace Dx12
        {
            class TextureLoader;
        }
    }

    namespace Renderer
    {
        namespace Dx12
        {
            class Device;
            class Context;
            class CommandQueue;
            class Descriptor;
            class CommandList;
            class DepthStencilBuffer;

            class BaseInstanced;


            class RenderLayerDx12 : public RenderLayer
            {
                public:
                RenderLayerDx12(Me::Window*);
                virtual ~RenderLayerDx12();

                void Clear(Colour) override;
                void Populate() override;
                void Present() override;
                void Submit(RenderComponent&, TransformComponent&) override;
                void SetCamera(CameraComponent&, TransformComponent&) override;
                
                Resources::Dx12::Mesh* CreateMesh(std::vector<Vertex>, std::vector<uint16_t>);
                Resources::Dx12::Texture* LoadTexture(std::string);
                Resources::Dx12::Texture* LoadTexture(const std::vector<unsigned char>, int, int);

                CommandList& GetCmd(int a_id = 0);
                Device& GetDevice();
                Context& GetContext();
                Descriptor& GetSRV();

                private:

                WindowsWindow* m_window = nullptr;
                
                Context* m_context = nullptr;
                Device* m_device = nullptr;

                Helper::Dx12::TextureLoader* m_textureLoader = nullptr;

                CommandQueue* m_queue = nullptr;
                Descriptor* m_rtv = nullptr;
                Descriptor* m_srv = nullptr;
                DepthStencilBuffer* m_dsBuffer = nullptr;
                std::vector<CommandList*> m_cmd;
                
                Helper::Dx12::UploadBuffer<Helper::Dx12::CameraBuffer>* m_camBuffer;
                std::vector<RenderComponent*> m_renderables;
                Resources::Dx12::Shader* m_activeShader;

                std::vector<BaseInstanced*> m_instancedRenderer;

                bool m_startUp;
                
                DirectX::XMFLOAT4X4 m_viewProjection;
            };
        }
    }
}