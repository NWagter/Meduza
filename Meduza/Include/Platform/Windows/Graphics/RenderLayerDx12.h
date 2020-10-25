#pragma once
#include "Platform/General/Graphics/RenderLayer.h"

namespace Me 
{
    class WindowsWindow;

    namespace Resources
    {
        namespace Dx12
        {
            class Mesh;
            class Shader;
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


            class RenderLayerDx12 : public RenderLayer
            {
                public:
                RenderLayerDx12(Me::Window*);
                virtual ~RenderLayerDx12();

                void Clear(Colour) override;
                void Present() override;
                void Submit(Renderable&) override;
                
                Resources::Dx12::Mesh* CreateMesh(std::vector<Vertex>, std::vector<uint16_t>);
                
                CommandList& GetCmd(int a_id = 0);
                Device& GetDevice();

                private:
                void Populate();

                WindowsWindow* m_window = nullptr;
                Context* m_context = nullptr;
                Device* m_device = nullptr;

                CommandQueue* m_queue = nullptr;
                Descriptor* m_rtv;
                Descriptor* m_srv;
                std::vector<CommandList*> m_cmd;
                
                std::vector<Renderable*> m_renderables;

                Resources::Dx12::Shader* m_activeShader;
            };
        }
    }
}